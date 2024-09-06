#pragma once

#include "webgpu-base.h"
#include "webgpu-buffer.h"
#include "webgpu-texture.h"

namespace rhi::webgpu {

class ResourceViewImpl : public ResourceViewBase
{
public:
    enum class ViewType
    {
        Texture,
        Buffer,
    };

public:

    ResourceViewImpl(ViewType viewType, DeviceImpl* device)
        : m_type(viewType)
        , m_device(device)
    {
    }
    ViewType m_type;
    RefPtr<DeviceImpl> m_device;

};

class BufferResourceViewImpl : public ResourceViewImpl
{
public:
    BufferResourceViewImpl(DeviceImpl* device)
        : ResourceViewImpl(ViewType::Buffer, device)
    {
    }
    ~BufferResourceViewImpl();
    RefPtr<BufferResourceImpl> m_buffer;
    Offset m_offset;
    Size m_size;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        getNativeHandle(InteropHandle* outHandle) override;

};
    
class TextureResourceViewImpl : public ResourceViewImpl
{
public:
    TextureResourceViewImpl(DeviceImpl* device)
        : ResourceViewImpl(ViewType::Texture, device)
    {
    }
    ~TextureResourceViewImpl();
    RefPtr<TextureResourceImpl> m_texture;
    WGPUTextureView m_textureView = {};

    virtual SLANG_NO_THROW Result SLANG_MCALL
        getNativeHandle(InteropHandle* outHandle) override;

};
    
} // namespace rhi::webgpu
