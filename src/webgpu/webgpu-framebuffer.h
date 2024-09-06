#pragma once

#include "webgpu-base.h"
#include "webgpu-device.h"

namespace rhi::webgpu {

class FramebufferLayoutImpl : public FramebufferLayoutBase
{

public:
    
    ~FramebufferLayoutImpl();
    Result init(DeviceImpl* renderer, const IFramebufferLayout::Desc& desc);    
    
};

class FramebufferImpl : public FramebufferBase
{

public:
    
    Result init(DeviceImpl* renderer, const IFramebuffer::Desc& desc);

};
 
} // namespace rhi::webgpu
