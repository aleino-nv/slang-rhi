#include "webgpu-framebuffer.h"

namespace rhi::webgpu {

FramebufferLayoutImpl::~FramebufferLayoutImpl()
{

}

Result
FramebufferLayoutImpl::init(DeviceImpl* renderer, const IFramebufferLayout::Desc& desc)
{
    return {};
}

Result FramebufferImpl::init(DeviceImpl* renderer, const IFramebuffer::Desc& desc)
{
    return {};
}
    
} // namespace rhi::webgpu
