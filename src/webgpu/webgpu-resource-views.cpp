#include "webgpu-resource-views.h"

namespace rhi::webgpu {

BufferResourceViewImpl::~BufferResourceViewImpl() {}

Result BufferResourceViewImpl::getNativeHandle(InteropHandle* outHandle)
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}
    
TextureResourceViewImpl::~TextureResourceViewImpl()
{
    if (m_textureView)
    {
        m_device->m_api.wgpuTextureViewRelease(m_textureView);
        m_textureView = {};
    }
}

Result
TextureResourceViewImpl::getNativeHandle(InteropHandle* outHandle)
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}    
    
} // namespace rhi::webgpu
