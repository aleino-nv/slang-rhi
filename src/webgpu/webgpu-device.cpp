#include "../resource-desc-utils.h"
#include "webgpu-device.h"
#include "webgpu-shader-program.h"
#include "webgpu-shader-object-layout.h"
#include "webgpu-transient-heap.h"
#include "webgpu-command-queue.h"
#include "webgpu-texture.h"
#include "webgpu-resource-views.h"
#include "webgpu-framebuffer.h"
#include "webgpu-render-pass.h"
#include "webgpu-pipeline-state.h"
#include "webgpu-buffer.h"

namespace rhi::webgpu {

DeviceImpl::~DeviceImpl()
{

	if(m_device)
	{
		m_api.wgpuDeviceRelease(m_device);
        m_device = {};
	}

	if(m_adapter)
	{
		m_api.wgpuAdapterRelease(m_adapter);
        m_adapter = {};
	}

    if(m_api.m_instance)
	{
		m_api.wgpuInstanceRelease(m_api.m_instance);
        m_api.m_instance = {};
	}

}

Result DeviceImpl::initWebGPUInstanceAndAdapterAndDevice()
{
    WGPUInstance instance = {};
    {
        WGPUInstanceDescriptor description = {};
        instance = m_api.wgpuCreateInstance(&description);
    }
    if (!instance)
        return SLANG_FAIL;
    SLANG_RETURN_ON_FAIL(m_api.initInstanceProcs(instance));

    WGPUAdapter adapter = {};
    {
		WGPURequestAdapterOptions options = {};
		options.powerPreference = WGPUPowerPreference_HighPerformance;
        options.backendType = WGPUBackendType_D3D12;
		WGPURequestAdapterCallback callback =
			[](
				WGPURequestAdapterStatus status,
				WGPUAdapter adapter,
				char const * /* message */,
				void * userdata
				) {

				switch(status)
				{

				case WGPURequestAdapterStatus_Success:
				{
					*reinterpret_cast<WGPUAdapter*>(userdata) = adapter;
				}
				break;

                default:
				case WGPURequestAdapterStatus_InstanceDropped:
				case WGPURequestAdapterStatus_Unknown:
				case WGPURequestAdapterStatus_Error:
				case WGPURequestAdapterStatus_Unavailable:
                    break;

				}

			};
		void *const userdata {&adapter};
		m_api.wgpuInstanceRequestAdapter(instance, &options, callback, userdata);
    }
    if (!instance)
        return SLANG_FAIL;
    m_adapter = adapter;
    SLANG_RETURN_ON_FAIL(m_api.initAdapterProcs(adapter));

    WGPUDevice device = {};
	{
		WGPURequestDeviceCallback callback =
			[](
               WGPURequestDeviceStatus status,
               WGPUDevice device,
               char const * message,
               void * userdata
               )
        {
            switch(status)
            {

            case WGPURequestDeviceStatus_Success:
            {
                *reinterpret_cast<WGPUDevice*>(userdata) = device;
            }
            break;

            case WGPURequestDeviceStatus_Error:
            case WGPURequestDeviceStatus_InstanceDropped:
            case WGPURequestDeviceStatus_Unknown:
            default:
                break;

            }
        };
        std::vector<WGPUFeatureName> const requiredFeatures {WGPUFeatureName_ShaderF16};
		WGPUDeviceDescriptor descriptor = {};
		// TODO:
        // Find some docs about callback modes. I'm just setting this to avoid error spew.
		descriptor.deviceLostCallbackInfo2.mode = WGPUCallbackMode_WaitAnyOnly;
        descriptor.requiredFeatureCount = requiredFeatures.size();
        descriptor.requiredFeatures = requiredFeatures.data();
		descriptor.deviceLostCallbackInfo2.callback =
			[](
				WGPUDevice const * /* device */,
				WGPUDeviceLostReason reason,
				char const * message,
				void* /* userdata1 */,
				void* /* userdata2 */
				) {

				switch(reason)
				{
				case WGPUDeviceLostReason_Destroyed:
					// TODO:
					// Figure out why releasing the instance after destroying the device
                    // generates WGPUDeviceLostReason_InstanceDropped. Is this a Dawn bug?
				case WGPUDeviceLostReason_InstanceDropped:
					break;

				case WGPUDeviceLostReason_FailedCreation:
				case WGPUDeviceLostReason_Unknown:
				default:
				{
                    SLANG_RHI_UNREACHABLE("Unexpected device loss");
				}

				}

			};
		descriptor.uncapturedErrorCallbackInfo2.callback =
			[](
				WGPUDevice const * /* device */,
				WGPUErrorType /* type */,
				char const * /* message */,
				void* /* userdata1 */,
				void* /* userdata2 */
				) {
                SLANG_RHI_UNREACHABLE("Unexpected error");
			};
        std::vector<char const*> const enabledToggles {"use_dxc"};
        WGPUDawnTogglesDescriptor togglesDescriptor = {};
        togglesDescriptor.chain.sType = WGPUSType_DawnTogglesDescriptor;
        togglesDescriptor.enabledToggleCount = enabledToggles.size();
        togglesDescriptor.enabledToggles = enabledToggles.data();
        descriptor.nextInChain = &togglesDescriptor.chain;
		void *const userdata {&device};
		m_api.wgpuAdapterRequestDevice(adapter, &descriptor, callback, userdata);
	}
    if (!device)
        return SLANG_FAIL;
    m_device = device;
    SLANG_RETURN_ON_FAIL(m_api.initDeviceProcs(device));

    return SLANG_OK;
}

Result DeviceImpl::initialize(const Desc& desc)
{

    {
        m_info.apiName = "WebGPU";
        m_info.deviceType = DeviceType::WebGPU;
        static const float kIdentity[] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
        ::memcpy(m_info.identityProjectionMatrix, kIdentity, sizeof(kIdentity));
    }

    m_desc = desc;

    SLANG_RETURN_ON_FAIL(RendererBase::initialize(desc));
    SLANG_RETURN_ON_FAIL(m_module.init());
    SLANG_RETURN_ON_FAIL(m_api.initGlobalProcs(m_module));

    // TODO: Use desc.existingDeviceHandles.handles if they are given, like the Vulkan
    // backend does?
    SLANG_RETURN_ON_FAIL(initWebGPUInstanceAndAdapterAndDevice());

    SLANG_RETURN_ON_FAIL(
        slangContext.initialize(
            desc.slang,
            desc.extendedDescCount,
            desc.extendedDescs,
            SLANG_WGSL,
            "",
            make_array(slang::PreprocessorMacroDesc{"__WEBGPU__", "1"})
        )
    );

}

Result
DeviceImpl::createTransientResourceHeap(
    const rhi::ITransientResourceHeap::Desc& desc,
    rhi::ITransientResourceHeap** outHeap
    )
{
    RefPtr<TransientResourceHeapImpl> result = new TransientResourceHeapImpl();
    SLANG_RETURN_ON_FAIL(result->init(desc, this));
    returnComPtr(outHeap, result);
    return SLANG_OK;
}

Result
DeviceImpl::createTextureResource(
    const rhi::ITextureResource::Desc& descIn,
    const rhi::ITextureResource::SubresourceData* initData,
    rhi::ITextureResource** outResource
    )
{
    TextureResource::Desc desc = fixupTextureDesc(descIn);
    RefPtr<TextureResourceImpl> texture(new TextureResourceImpl(desc, this));
    returnComPtr(outResource, texture);
    return SLANG_OK;
}

Result
DeviceImpl::createBufferResource(
    const rhi::IBufferResource::Desc& descIn,
    const void* initData,
    rhi::IBufferResource** outBufferResource
    )
{
    BufferResource::Desc desc = fixupBufferDesc(descIn);    

    RefPtr<BufferResourceImpl> bufferResource(new BufferResourceImpl(desc, this));    
    returnComPtr(outBufferResource, bufferResource);
    return SLANG_OK;
}

Result
DeviceImpl::createSamplerState(
    const rhi::ISamplerState::Desc &,
    rhi::ISamplerState **
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

Result
DeviceImpl::createTextureView(
    rhi::ITextureResource* texture,
    const rhi::IResourceView::Desc& desc,
    rhi::IResourceView** outView
    )
{
    RefPtr<TextureResourceViewImpl> viewImpl = new TextureResourceViewImpl(this);
    returnComPtr(outView, viewImpl);
    return SLANG_OK;
}

Result
DeviceImpl::createBufferView(
    rhi::IBufferResource* buffer,
    rhi::IBufferResource* counterBuffer,
    const rhi::IResourceView::Desc& desc,
    rhi::IResourceView** outView
    )
{
    RefPtr<BufferResourceViewImpl> view = new BufferResourceViewImpl(this);    
    returnComPtr(outView, view);
    return SLANG_OK;
}

Result
DeviceImpl::createFramebufferLayout(
    const rhi::IFramebufferLayout::Desc& desc,
    rhi::IFramebufferLayout** outLayout
    )
{
    RefPtr<FramebufferLayoutImpl> layout = new FramebufferLayoutImpl();
    SLANG_RETURN_ON_FAIL(layout->init(this, desc));
    returnComPtr(outLayout, layout);
    return SLANG_OK;
}

Result
DeviceImpl::createFramebuffer(
    const rhi::IFramebuffer::Desc& desc,
    rhi::IFramebuffer** outFramebuffer
    )
{
    RefPtr<FramebufferImpl> framebuffer = new FramebufferImpl();
    SLANG_RETURN_ON_FAIL(framebuffer->init(this, desc));
    returnComPtr(outFramebuffer, framebuffer);
    return SLANG_OK;
}

Result
DeviceImpl::createRenderPassLayout(
    const rhi::IRenderPassLayout::Desc& desc,
    rhi::IRenderPassLayout** outRenderPassLayout
    )
{
    RefPtr<RenderPassLayoutImpl> renderPassLayout = new RenderPassLayoutImpl();
    SLANG_RETURN_ON_FAIL(renderPassLayout->init(this, desc));
    returnComPtr(outRenderPassLayout, renderPassLayout);
    return SLANG_OK;
}

Result
DeviceImpl::createSwapchain(
    const rhi::ISwapchain::Desc &,
    rhi::WindowHandle,
    rhi::ISwapchain **
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

Result
DeviceImpl::createInputLayout(
    const rhi::IInputLayout::Desc &,
    rhi::IInputLayout **
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

Result
DeviceImpl::createCommandQueue(
    const rhi::ICommandQueue::Desc& desc,
    rhi::ICommandQueue** outQueue
    )
{
    // Only support one queue for now.
    if (m_queueAllocCount != 0)
        return SLANG_FAIL;

    RefPtr<CommandQueueImpl> result = new CommandQueueImpl;
    WGPUQueue wgpuQueue = m_api.wgpuDeviceGetQueue(m_api.m_device);
    if(!wgpuQueue)
        return SLANG_FAIL;
    result->init(this, wgpuQueue);
    returnComPtr(outQueue, result);
    m_queueAllocCount++;
    return SLANG_OK;
}

Result
DeviceImpl::createProgram(
    const rhi::IShaderProgram::Desc& desc,
    rhi::IShaderProgram** outProgram,
    ISlangBlob** outDiagnosticBlob
    )
{
    RefPtr<ShaderProgramImpl> shaderProgram = new ShaderProgramImpl(this);
    shaderProgram->init(desc);

    RootShaderObjectLayoutImpl::create(
        this,
        shaderProgram->linkedProgram,
        shaderProgram->linkedProgram->getLayout(),
        shaderProgram->m_rootObjectLayout.writeRef()
    );

    if (!shaderProgram->isSpecializable())
    {
        SLANG_RETURN_ON_FAIL(shaderProgram->compileShaders(this));
    }

    returnComPtr(outProgram, shaderProgram);
    return SLANG_OK;
}

Result
DeviceImpl::createGraphicsPipelineState(
    const rhi::GraphicsPipelineStateDesc &,
    rhi::IPipelineState **
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

Result
DeviceImpl::createComputePipelineState(
    const rhi::ComputePipelineStateDesc& desc,
    rhi::IPipelineState** outState
    )
{
    RefPtr<PipelineStateImpl> state = new PipelineStateImpl(this);
    state->init(desc);
    returnComPtr(outState, state);
    return SLANG_OK;
}

Result
DeviceImpl::createQueryPool(
    const rhi::IQueryPool::Desc &,
    rhi::IQueryPool **
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

Result
DeviceImpl::createShaderObject(
    rhi::ShaderObjectLayoutBase *,
    rhi::IShaderObject **
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

Result
DeviceImpl::createMutableShaderObject(
    rhi::ShaderObjectLayoutBase *,
    rhi::IShaderObject **
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

Result
DeviceImpl::createShaderObjectLayout(
    slang::ISession *,
    slang::TypeLayoutReflection *,
    rhi::ShaderObjectLayoutBase **
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

Result
DeviceImpl::readTextureResource(
    rhi::ITextureResource *,
    rhi::ResourceState,
    ISlangBlob **,
    rhi::Size *,
    rhi::Size *
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

Result
DeviceImpl::readBufferResource(
    rhi::IBufferResource *,
    rhi::Offset,
    rhi::Size,
    ISlangBlob **
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

SLANG_NO_THROW const DeviceInfo& SLANG_MCALL DeviceImpl::getDeviceInfo() const
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

} // namespace rhi::webgpu
