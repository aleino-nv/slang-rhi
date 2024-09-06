#pragma once

#include "webgpu-base.h"
#include "webgpu-device.h"

namespace rhi::webgpu {

class RenderPassLayoutImpl : public IRenderPassLayout, public ComObject
{
public:
    SLANG_COM_OBJECT_IUNKNOWN_ALL
    IRenderPassLayout* getInterface(const Guid& guid);

public:
    
    ~RenderPassLayoutImpl();
    Result init(DeviceImpl* renderer, const IRenderPassLayout::Desc& desc);
};    
    
} // namespace rhi::webgpu
