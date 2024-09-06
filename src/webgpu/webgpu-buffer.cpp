#include "webgpu-buffer.h"

namespace rhi::webgpu {

BufferResourceImpl::BufferResourceImpl(
    const IBufferResource::Desc& desc, DeviceImpl* renderer
    ) :
    Parent(desc),
    m_renderer(renderer)
{
    SLANG_RHI_ASSERT(renderer);
}

DeviceAddress
BufferResourceImpl::getDeviceAddress()
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

Result
BufferResourceImpl::getNativeResourceHandle(InteropHandle* outHandle)
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

Result
BufferResourceImpl::getSharedHandle(InteropHandle* outHandle)
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

Result
BufferResourceImpl::map(MemoryRange* rangeToRead, void** outPointer)
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

Result
BufferResourceImpl::unmap(MemoryRange* writtenRange)
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

Result
BufferResourceImpl::setDebugName(const char* name)
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}
    
} // namespace rhi::webgpu
