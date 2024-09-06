#include "webgpu-shader-object.h"

namespace rhi::webgpu {

Result
ShaderObjectImpl::init(ShaderObjectLayoutImpl* layout)
{
    m_layout = layout;
    // TODO
    return SLANG_OK;
}    
    
Result
ShaderObjectImpl::setData(ShaderOffset const& inOffset, void const* data, size_t inSize)
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

Result
ShaderObjectImpl::setResource(ShaderOffset const& offset, IResourceView* resourceView)
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

Result
ShaderObjectImpl::setSampler(ShaderOffset const& offset, ISamplerState* sampler)
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}
    
Result RootShaderObjectImpl::init(RootShaderObjectLayoutImpl* layout)
{
    SLANG_RETURN_ON_FAIL(Super::init(layout));
    // TODO: Add entry points
    return SLANG_OK;
}

} // namespace rhi::webgpu
