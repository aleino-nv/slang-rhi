#pragma once

#include "webgpu-base.h"
#include "webgpu-device.h"

namespace rhi::webgpu {

class CommandQueueImpl : public ICommandQueue, public ComObject
{
public:
    SLANG_COM_OBJECT_IUNKNOWN_ALL
    ICommandQueue* getInterface(const Guid& guid);

public:

    Desc m_desc;

    WGPUQueue m_queue = {};
    RefPtr<DeviceImpl> m_renderer;    
    ~CommandQueueImpl();

    void init(DeviceImpl* device, WGPUQueue queue);

    virtual SLANG_NO_THROW void SLANG_MCALL
        waitOnHost() override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        getNativeHandle(InteropHandle* outHandle) override;

    virtual SLANG_NO_THROW const Desc& SLANG_MCALL
        getDesc() override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        waitForFenceValuesOnDevice(
            GfxCount fenceCount, IFence** fences, uint64_t* waitValues
        ) override;

    virtual SLANG_NO_THROW void SLANG_MCALL
        executeCommandBuffers(
            GfxCount count,
            ICommandBuffer* const* commandBuffers,
            IFence* fence,
            uint64_t valueToSignal
        ) override;

};

} // namespace rhi::webgpu
