#pragma once

#include "webgpu-shader-object-layout.h"

namespace rhi::webgpu {

class ShaderObjectImpl :
    public
    ShaderObjectBaseImpl<ShaderObjectImpl, ShaderObjectLayoutImpl, SimpleShaderObjectData>
{
public:

    SLANG_NO_THROW GfxCount SLANG_MCALL
        getEntryPointCount() SLANG_OVERRIDE { return 0; }

    SLANG_NO_THROW Result SLANG_MCALL
        getEntryPoint(GfxIndex index, IShaderObject** outEntryPoint) SLANG_OVERRIDE
    {
        *outEntryPoint = nullptr;
        return SLANG_OK;
    }

    virtual SLANG_NO_THROW const void* SLANG_MCALL
        getRawData() override
    {
        SLANG_RHI_UNREACHABLE("Not implemented");
        return {};
    }

    virtual SLANG_NO_THROW size_t SLANG_MCALL
        getSize() override
    {
        SLANG_RHI_UNREACHABLE("Not implemented");
        return {};
    }

    SLANG_NO_THROW Result SLANG_MCALL
        setData(ShaderOffset const& inOffset, void const* data, size_t inSize)
        SLANG_OVERRIDE;

    SLANG_NO_THROW Result SLANG_MCALL
        setResource(ShaderOffset const& offset, IResourceView* resourceView)
        SLANG_OVERRIDE;

    SLANG_NO_THROW Result SLANG_MCALL
        setSampler(ShaderOffset const& offset, ISamplerState* sampler) SLANG_OVERRIDE;

    SLANG_NO_THROW Result SLANG_MCALL
        setCombinedTextureSampler(
            ShaderOffset const& offset, IResourceView* textureView, ISamplerState* sampler
        ) SLANG_OVERRIDE
    {
        return SLANG_E_NOT_IMPLEMENTED;
    }

protected:
    
    Result init(ShaderObjectLayoutImpl* layout);
    
};
    
class RootShaderObjectImpl : public ShaderObjectImpl
{
    typedef ShaderObjectImpl Super;
    
public:

    Result init(RootShaderObjectLayoutImpl* layout);

};
    
} // namespace rhi::webgpu
