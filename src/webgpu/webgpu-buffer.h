#pragma once

#include "webgpu-base.h"
#include "webgpu-device.h"

namespace rhi::webgpu {
    
class BufferResourceImpl : public BufferResource
{

public:

    typedef BufferResource Parent;
    
    BufferResourceImpl(const IBufferResource::Desc& desc, DeviceImpl* renderer);

    RefPtr<DeviceImpl> m_renderer;
    
    virtual SLANG_NO_THROW DeviceAddress SLANG_MCALL
        getDeviceAddress() override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        getNativeResourceHandle(InteropHandle* outHandle) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        getSharedHandle(InteropHandle* outHandle) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        map(MemoryRange* rangeToRead, void** outPointer) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        unmap(MemoryRange* writtenRange) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        setDebugName(const char* name) override;

};

} // namespace rhi::webgpu
