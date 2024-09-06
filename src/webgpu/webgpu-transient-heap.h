#pragma once

#include "webgpu-base.h"
#include "webgpu-buffer.h"
#include "webgpu-device.h"
#include "webgpu-command-buffer.h"

namespace rhi::webgpu {

class TransientResourceHeapImpl :
    public TransientResourceHeapBaseImpl<DeviceImpl, BufferResourceImpl>
{

private:

    typedef TransientResourceHeapBaseImpl<DeviceImpl, BufferResourceImpl> Super;

public:

    WGPUCommandEncoder m_commandEncoder = {};

    Result init(const ITransientResourceHeap::Desc& desc, DeviceImpl* device);
    ~TransientResourceHeapImpl();

public:

    virtual SLANG_NO_THROW Result SLANG_MCALL
        createCommandBuffer(ICommandBuffer** outCommandBuffer) override;

    virtual SLANG_NO_THROW Result
        SLANG_MCALL synchronizeAndReset() override;

};

} // namespace rhi::webgpu
