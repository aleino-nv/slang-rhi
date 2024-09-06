#pragma once

#include "webgpu-base.h"
#include "webgpu-device.h"

namespace rhi::webgpu {

class PipelineStateImpl : public PipelineStateBase
{

public:
    
    PipelineStateImpl(DeviceImpl* device);
    ~PipelineStateImpl();
    
    void init(const ComputePipelineStateDesc& inDesc);

    virtual Result
        ensureAPIPipelineStateCreated() override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        getNativeHandle(InteropHandle* outHandle) override;

    
    
};

} // namespace rhi::webgpu
