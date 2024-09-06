#pragma once

#include "webgpu-base.h"
#include "webgpu-shader-object-layout.h"

namespace rhi::webgpu {

class DeviceImpl;
    
class ShaderProgramImpl : public ShaderProgramBase
{
public:

    DeviceImpl* m_device;    
    RefPtr<RootShaderObjectLayoutImpl> m_rootObjectLayout;
    std::vector<WGPUShaderModule> m_modules;

    ShaderProgramImpl(DeviceImpl* device);
    ~ShaderProgramImpl();
    
    virtual Result
        createShaderModule(
            slang::EntryPointReflection* entryPointInfo, ComPtr<ISlangBlob> kernelCode
        ) override;

};

} // namespace rhi::webgpu
