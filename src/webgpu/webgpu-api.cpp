#include "webgpu-api.h"

#include "core/assert.h"

namespace rhi::webgpu {

#define WEBGPU_API_CHECK_FUNCTION(x) &&(wgpu##x != nullptr)
#define WEBGPU_API_CHECK_FUNCTIONS(list) true list(WEBGPU_API_CHECK_FUNCTION)

bool WebGPUApi::areDefined(ProcType type) const
{

    switch (type)
    {
    case ProcType::Global:
        return WEBGPU_API_CHECK_FUNCTIONS(WEBGPU_API_ALL_GLOBAL_PROCS);
    case ProcType::Instance:
        return WEBGPU_API_CHECK_FUNCTIONS(WEBGPU_API_ALL_INSTANCE_PROCS);
    case ProcType::Adapter:
        return WEBGPU_API_CHECK_FUNCTIONS(WEBGPU_API_ALL_ADAPTER_PROCS);
    case ProcType::Device:
        return WEBGPU_API_CHECK_FUNCTIONS(WEBGPU_API_ALL_DEVICE_PROCS);
    default:
    {
        SLANG_RHI_ASSERT_FAILURE("Unhandled type");
        return false;
    }
    }

}

Result WebGPUApi::initGlobalProcs(const WebGPUModule& module)
{
#define WEBGPU_API_GET_GLOBAL_PROC(x)                                                    \
    wgpu##x = (WGPUProc##x)module.getFunction("wgpu"#x);
    WEBGPU_API_ALL_GLOBAL_PROCS(WEBGPU_API_GET_GLOBAL_PROC)
#undef WEBGPU_API_GET_GLOBAL_PROC

    if (!areDefined(ProcType::Global))
    {
        return SLANG_FAIL;
    }

    m_module = &module;
    return SLANG_OK;
}

Result WebGPUApi::initInstanceProcs(WGPUInstance instance)
{
    SLANG_RHI_ASSERT(instance != nullptr);
#define WEBGPU_API_GET_INSTANCE_PROC(x)                                                  \
    wgpu##x = (WGPUProc##x)m_module->getFunction("wgpu"#x);
    WEBGPU_API_ALL_INSTANCE_PROCS(WEBGPU_API_GET_INSTANCE_PROC)

    if (!areDefined(ProcType::Instance))
    {
        return SLANG_FAIL;
    }

    m_instance = instance;
    return SLANG_OK;
}

Result WebGPUApi::initAdapterProcs(WGPUAdapter adapter)
{
    SLANG_RHI_ASSERT(adapter != nullptr);
#define WEBGPU_API_GET_ADAPTER_PROC(x)                                                   \
    wgpu##x = (WGPUProc##x)m_module->getFunction("wgpu"#x);
    WEBGPU_API_ALL_ADAPTER_PROCS(WEBGPU_API_GET_ADAPTER_PROC)

    if (!areDefined(ProcType::Adapter))
    {
        return SLANG_FAIL;
    }

    m_adapter = adapter;
    return SLANG_OK;
}

Result WebGPUApi::initDeviceProcs(WGPUDevice device)
{
    SLANG_RHI_ASSERT(device != nullptr);
#define WEBGPU_API_GET_DEVICE_PROC(x)                                                    \
    wgpu##x = (WGPUProc##x)m_module->getFunction("wgpu"#x);
    WEBGPU_API_ALL_DEVICE_PROCS(WEBGPU_API_GET_DEVICE_PROC)

    if (!areDefined(ProcType::Device))
    {
        return SLANG_FAIL;
    }

    m_device = device;
    return SLANG_OK;
}

} // namespace rhi::webgpu
