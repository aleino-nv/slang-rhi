#include "webgpu-pipeline-state.h"

namespace rhi::webgpu {

PipelineStateImpl::PipelineStateImpl(DeviceImpl* device)
{
}

PipelineStateImpl::~PipelineStateImpl()
{

}

void PipelineStateImpl::init(const ComputePipelineStateDesc& desc)
{
    PipelineStateDesc pipelineDesc;
    pipelineDesc.type = PipelineType::Compute;
    pipelineDesc.compute = desc;
    initializeBase(pipelineDesc);
}

Result PipelineStateImpl::ensureAPIPipelineStateCreated()
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

SLANG_NO_THROW Result SLANG_MCALL
PipelineStateImpl::getNativeHandle(InteropHandle* outHandle)
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

} // namespace rhi::webgpu
