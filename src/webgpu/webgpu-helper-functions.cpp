#include "webgpu-helper-functions.h"
#include "webgpu-device.h"

namespace rhi {

Result SLANG_MCALL getWebGPUAdapters(std::vector<AdapterInfo>& outAdapters)
{
    webgpu::WebGPUModule module;
    if (module.init() != SLANG_OK)
        return SLANG_FAIL;
    webgpu::WebGPUApi api;
    if (api.initGlobalProcs(module) != SLANG_OK)
        return SLANG_FAIL;

    struct Handles
    {
        Handles(const webgpu::WebGPUApi &api) : m_api(api) {}
        WGPUInstance wgpuInstance = {};
        ~Handles()
        {
            if (wgpuInstance)
            {
                m_api.wgpuInstanceRelease(wgpuInstance);
            }
        }
    private:
        const webgpu::WebGPUApi& m_api;
    } handles(api);
    
    {
        WGPUInstanceDescriptor description = {};
        description.nextInChain = nullptr;
        handles.wgpuInstance = api.wgpuCreateInstance(&description);
        if (!handles.wgpuInstance)
            return SLANG_FAIL;
    }

    std::vector<AdapterInfo> adapters;
	{
        struct Context
        {
            webgpu::WebGPUApi& api;
            std::vector<AdapterInfo>& adapters;
        };

		WGPUAdapter adapter = {};
		WGPURequestAdapterOptions options = {};
		options.powerPreference = WGPUPowerPreference_HighPerformance;
        options.backendType = WGPUBackendType_D3D12;
		WGPURequestAdapterCallback callback =
			[](
				WGPURequestAdapterStatus status,
				WGPUAdapter adapter,
				char const * /* message */,
				void * userdata
				)
            {
                Context& context = *static_cast<Context*>(userdata);

				switch(status)
				{

				case WGPURequestAdapterStatus_Success:
				{
                    WGPUAdapterInfo wgpuInfo = {};
                    WGPUStatus const infoStatus =
                        context.api.wgpuAdapterGetInfo(adapter, &wgpuInfo);
                    AdapterInfo info = {};
                    if (infoStatus == WGPUStatus_Success)
                    {
                        const char* name = wgpuInfo.device;
                        memcpy(
                               info.name, name,
                               std::min(strlen(name), sizeof(AdapterInfo::name) - 1));
                        uint32_t adapterId[4] =
                        {
                            wgpuInfo.vendorID,
                            wgpuInfo.deviceID,
                            static_cast<uint32_t>(wgpuInfo.backendType),
                            static_cast<uint32_t>(wgpuInfo.adapterType)
                        };
                        SLANG_RHI_ASSERT(sizeof(adapterId) == sizeof(info.luid.luid));
                        memcpy(&info.luid.luid[0], &adapterId, sizeof(adapterId));
                    }
                    context.adapters.push_back(info);
				}
				break;

				case WGPURequestAdapterStatus_Error:
				case WGPURequestAdapterStatus_InstanceDropped:
				case WGPURequestAdapterStatus_Unavailable:
				case WGPURequestAdapterStatus_Unknown:
					break;

				}

			};
        Context context {api, adapters};
		void *const userdata = &context;
		api.wgpuInstanceRequestAdapter(
            handles.wgpuInstance, &options, callback, userdata
        );
		if(adapters.empty())
		{
            return SLANG_FAIL;
		}
	}

    outAdapters = std::move(adapters);
    return SLANG_OK;
}

Result SLANG_MCALL createWebGPUDevice(const IDevice::Desc* desc, IDevice** outRenderer)
{
    RefPtr<webgpu::DeviceImpl> result = new webgpu::DeviceImpl();
    SLANG_RETURN_ON_FAIL(result->initialize(*desc));
    returnComPtr(outRenderer, result);
    return SLANG_OK;
}

} // namespace rhi
