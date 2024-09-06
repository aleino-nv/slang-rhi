#include "webgpu-render-pass.h"

namespace rhi::webgpu {

IRenderPassLayout* RenderPassLayoutImpl::getInterface(const Guid& guid)
{
    if (guid == GUID::IID_ISlangUnknown || guid == GUID::IID_IRenderPassLayout)
        return static_cast<IRenderPassLayout*>(this);
    return nullptr;
}

RenderPassLayoutImpl::~RenderPassLayoutImpl()
{
}

Result
RenderPassLayoutImpl::init(DeviceImpl* renderer, const IRenderPassLayout::Desc& desc)
{
    return {};
}
    
} // namespace rhi::webgpu
