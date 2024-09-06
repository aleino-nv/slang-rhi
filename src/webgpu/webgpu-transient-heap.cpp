#include "webgpu-transient-heap.h"

namespace rhi::webgpu {

TransientResourceHeapImpl::~TransientResourceHeapImpl()
{
    if (m_commandEncoder)
    {
        m_device->m_api.wgpuCommandEncoderRelease(m_commandEncoder);
        m_commandEncoder = {};
    }
}
    
Result TransientResourceHeapImpl::init(
    const ITransientResourceHeap::Desc& desc, DeviceImpl* device
    )
{
    WGPUCommandEncoderDescriptor descriptor = {};
    WGPUCommandEncoder encoder =
        device->m_api.wgpuDeviceCreateCommandEncoder(
            device->m_api.m_device, &descriptor
        );
    if (!encoder)
        return SLANG_FAIL;

    m_commandEncoder = encoder;
    return SLANG_OK;
}
    
Result TransientResourceHeapImpl::createCommandBuffer(ICommandBuffer** outCmdBuffer)
{
    RefPtr<CommandBufferImpl> commandBuffer = new CommandBufferImpl();
    SLANG_RETURN_ON_FAIL(commandBuffer->init(m_device, this));
    returnComPtr(outCmdBuffer, commandBuffer);
    return SLANG_OK;
}

Result TransientResourceHeapImpl::synchronizeAndReset()
{
    SLANG_RHI_UNREACHABLE("Not implemented");    
    return SLANG_FAIL;
}
    
} // namespace rhi::webgpu
