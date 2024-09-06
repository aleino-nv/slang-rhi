#include "webgpu-command-queue.h"

namespace rhi::webgpu {

ICommandQueue* CommandQueueImpl::getInterface(const Guid& guid)
{
    if (guid == GUID::IID_ISlangUnknown || guid == GUID::IID_ICommandQueue)
        return static_cast<ICommandQueue*>(this);
    return nullptr;
}
    
CommandQueueImpl::~CommandQueueImpl()
{
    if (m_queue)
    {
        m_renderer->m_api.wgpuQueueRelease(m_queue);
        m_queue = {};
        m_renderer->m_queueAllocCount--;
    }
}
    
void CommandQueueImpl::init(DeviceImpl* renderer, WGPUQueue queue)
{
    SLANG_RHI_ASSERT(queue != WGPUQueue{});
    m_renderer = renderer;
    m_queue = queue;
}

void
CommandQueueImpl::waitOnHost()
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}

Result
CommandQueueImpl::getNativeHandle(InteropHandle* outHandle)
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

const CommandQueueImpl::Desc&
CommandQueueImpl::getDesc()
{
    return m_desc;
}

Result
CommandQueueImpl::waitForFenceValuesOnDevice(
    GfxCount fenceCount, IFence** fences, uint64_t* waitValues
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

void
CommandQueueImpl::executeCommandBuffers(
    GfxCount count,
    ICommandBuffer* const* commandBuffers,
    IFence* fence,
    uint64_t valueToSignal
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}
    
} // namespace rhi::webgpu
