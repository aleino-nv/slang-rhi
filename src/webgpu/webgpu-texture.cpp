#include "webgpu-texture.h"

namespace rhi::webgpu {

TextureResourceImpl::TextureResourceImpl(const Desc& desc, DeviceImpl* device)
    : Parent(desc)
    , m_device(device)
{
}

TextureResourceImpl::~TextureResourceImpl()
{
    if (m_texture)
    {
        m_device->m_api.wgpuTextureRelease(m_texture);
        m_texture = {};
    }
}
    
Result TextureResourceImpl::getNativeResourceHandle(InteropHandle* outHandle)
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

Result TextureResourceImpl::getSharedHandle(InteropHandle* outHandle)
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};    
}

Result TextureResourceImpl::setDebugName(const char* name)
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}
    
} // namespace rhi::webgpu
