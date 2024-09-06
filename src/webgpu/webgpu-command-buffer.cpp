#include "webgpu-command-buffer.h"
#include "webgpu-command-encoder.h"

namespace rhi::webgpu {

ICommandBuffer* CommandBufferImpl::getInterface(const Guid& guid)
{
    if (guid == GUID::IID_ISlangUnknown || guid == GUID::IID_ICommandBuffer)
        return static_cast<ICommandBuffer*>(this);
    return nullptr;
}
    
Result
CommandBufferImpl::init(DeviceImpl* device, TransientResourceHeapImpl* transientHeap)
{
    return {};
}

void
CommandBufferImpl::encodeRenderCommands(
    IRenderPassLayout* renderPass,
    IFramebuffer* framebuffer,
    IRenderCommandEncoder** outEncoder
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}

void
CommandBufferImpl::encodeComputeCommands(IComputeCommandEncoder** outEncoder)
{
    if (!m_computeCommandEncoder)
    {
        m_computeCommandEncoder = new ComputeCommandEncoder();
        m_computeCommandEncoder->init(this);
    }
    *outEncoder = m_computeCommandEncoder.Ptr();
}

void
CommandBufferImpl::encodeResourceCommands(IResourceCommandEncoder** outEncoder)
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}

void
CommandBufferImpl::encodeRayTracingCommands(IRayTracingCommandEncoder** outEncoder)
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}

void
CommandBufferImpl::close()
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}

Result
CommandBufferImpl::getNativeHandle(InteropHandle* outHandle)
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}

} // namespace rhi::webgpu
