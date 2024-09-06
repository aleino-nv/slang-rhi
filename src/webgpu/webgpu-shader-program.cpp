#include "webgpu-device.h"
#include "webgpu-shader-program.h"

namespace rhi::webgpu {

ShaderProgramImpl::ShaderProgramImpl(DeviceImpl* device)
    : m_device(device)
{
}

ShaderProgramImpl::~ShaderProgramImpl()
{
    for (WGPUShaderModule shaderModule : m_modules)
    {
        if (shaderModule)
        {
            m_device->m_api.wgpuShaderModuleRelease(shaderModule);
        }
    }
}

Result
ShaderProgramImpl::createShaderModule(
    slang::EntryPointReflection* entryPointInfo, ComPtr<ISlangBlob> kernelCode
    )
{
    WGPUShaderModule module = {};
	{
		WGPUShaderModuleWGSLDescriptor wgslDescriptor = {};
		wgslDescriptor.chain.sType = WGPUSType_ShaderModuleWGSLDescriptor;
        std::vector<char> wgslCode(
            (char*)kernelCode->getBufferPointer(),
            (char*)kernelCode->getBufferPointer() + kernelCode->getBufferSize()
        );
        wgslCode.push_back('\0');
		wgslDescriptor.code = wgslCode.data();
		WGPUShaderModuleDescriptor descriptor = {};
		descriptor.nextInChain = &wgslDescriptor.chain;
		module =
            m_device->m_api.wgpuDeviceCreateShaderModule(
                m_device->m_api.m_device, &descriptor
            );
		if (!module)
        {
            return SLANG_E_INVALID_ARG;
        }
	}
    
    m_modules.push_back(module);
    return SLANG_OK;
}
    
} // namespace rhi::webgpu
