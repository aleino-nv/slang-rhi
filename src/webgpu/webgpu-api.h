#pragma once

#include "webgpu-module.h"

namespace rhi::webgpu {

#define WEBGPU_API_GLOBAL_PROCS(x)                                                       \
    x(CreateInstance)

#define WEBGPU_API_ADAPTER_PROCS(x)                                                      \
    x(AdapterGetInfo)                                                                    \
    x(AdapterRelease)                                                                    \
    x(AdapterRequestDevice)

#define WEBGPU_API_INSTANCE_PROCS(x)                                                     \
    x(InstanceRelease)                                                                   \
    x(InstanceRequestAdapter)

#define WEBGPU_API_DEVICE_PROCS(x)                                                       \
    x(DeviceRelease)                                                                     \
    x(DeviceCreateShaderModule)                                                          \
    x(DeviceCreateCommandEncoder)                                                        \
    x(DeviceGetQueue)                                                                    \
    x(ShaderModuleRelease)                                                               \
    x(CommandEncoderRelease)                                                             \
    x(QueueRelease)                                                                      \
    x(TextureRelease)                                                                    \
    x(TextureViewRelease)

#define WEBGPU_API_ALL_GLOBAL_PROCS(x)                                                   \
    WEBGPU_API_GLOBAL_PROCS(x)

#define WEBGPU_API_ALL_ADAPTER_PROCS(x)                                                  \
    WEBGPU_API_ADAPTER_PROCS(x)

#define WEBGPU_API_ALL_INSTANCE_PROCS(x)                                                 \
    WEBGPU_API_INSTANCE_PROCS(x)

#define WEBGPU_API_ALL_DEVICE_PROCS(x)                                                   \
    WEBGPU_API_DEVICE_PROCS(x)

#define WEBGPU_API_ALL_PROCS(x)                                                          \
    WEBGPU_API_ALL_GLOBAL_PROCS(x)                                                       \
    WEBGPU_API_ALL_ADAPTER_PROCS(x)                                                      \
    WEBGPU_API_ALL_INSTANCE_PROCS(x)                                                     \
    WEBGPU_API_ALL_DEVICE_PROCS(x)

#define WEBGPU_API_DECLARE_PROC(NAME) WGPUProc##NAME wgpu##NAME = nullptr;

struct WebGPUApi
{
    WEBGPU_API_ALL_PROCS(WEBGPU_API_DECLARE_PROC)

    enum class ProcType
    {
        Global,
        Instance,
        Adapter,
        Device,
    };

    /// Returns true if all the functions in the class are defined
    bool areDefined(ProcType type) const;

    /// Sets up global parameters
    Result initGlobalProcs(const WebGPUModule& module);

    /// Initialize the instance functions
    Result initInstanceProcs(WGPUInstance instance);

    /// Initialize the adapter functions
    Result initAdapterProcs(WGPUAdapter adapter);

    /// Initialize the device functions
    Result initDeviceProcs(WGPUDevice device);

    WGPUInstance m_instance = nullptr;
    WGPUAdapter m_adapter = nullptr;
    WGPUDevice m_device = nullptr;

private:

    /// Module this was all loaded from.
    const WebGPUModule* m_module = nullptr;

};

} // namespace rhi::webgpu
