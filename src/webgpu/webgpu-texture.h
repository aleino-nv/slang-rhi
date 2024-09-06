#pragma once

#include "webgpu-base.h"
#include "webgpu-device.h"

namespace rhi::webgpu {

class TextureResourceImpl : public TextureResource
{
public:
    typedef TextureResource Parent;
    
    TextureResourceImpl(const Desc& desc, DeviceImpl* device);
    ~TextureResourceImpl();

    WGPUTexture m_texture = {};
    
    RefPtr<DeviceImpl> m_device;
    
    virtual SLANG_NO_THROW Result SLANG_MCALL
        getNativeResourceHandle(InteropHandle* outHandle) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        getSharedHandle(InteropHandle* outHandle) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        setDebugName(const char* name) override;
};

} // namespace rhi::webgpu
