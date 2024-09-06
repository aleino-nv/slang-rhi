#include "webgpu-command-encoder.h"
#include "webgpu-command-buffer.h"
#include "webgpu-shader-program.h"

namespace rhi::webgpu {

void PipelineCommandEncoder::init(CommandBufferImpl* commandBuffer)
{
    m_commandBuffer = commandBuffer;
}

Result
PipelineCommandEncoder::setPipelineStateImpl(
    IPipelineState* state, IShaderObject** outRootObject
    )
{
    m_currentPipeline = static_cast<PipelineStateImpl*>(state);

    SLANG_RETURN_ON_FAIL(
        m_commandBuffer->m_rootObject.init(
            m_currentPipeline->getProgram<ShaderProgramImpl>()->m_rootObjectLayout
        )
    );

    *outRootObject = &m_commandBuffer->m_rootObject;
    return SLANG_OK;
}
    
void*
ResourceCommandEncoder::getInterface(SlangUUID const& guid)
{
    if (guid == GUID::IID_IResourceCommandEncoder || guid == ISlangUnknown::getTypeGuid())
        return this;
    return nullptr;
}

Result
ResourceCommandEncoder::queryInterface(SlangUUID const& uuid, void** outObject)
{
    if (auto ptr = getInterface(uuid))
    {
        *outObject = ptr;
        return SLANG_OK;
    }
    return SLANG_E_NO_INTERFACE;
}

void 
ResourceCommandEncoder::copyBuffer(
    IBufferResource* dst,
    Offset dstOffset,
    IBufferResource* src,
    Offset srcOffset,
    Size size
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}
    
void 
ResourceCommandEncoder::uploadBufferData(
    IBufferResource* buffer, Offset offset, Size size, void* data
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}
    
void 
ResourceCommandEncoder::textureBarrier(
    GfxCount count,
    ITextureResource* const* textures,
    ResourceState src,
    ResourceState dst
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}
    
void 
ResourceCommandEncoder::bufferBarrier(
    GfxCount count,
    IBufferResource* const* buffers,
    ResourceState src,
    ResourceState dst
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}
    
void 
ResourceCommandEncoder::endEncoding()
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}
    
void 
ResourceCommandEncoder::writeTimestamp(IQueryPool* queryPool, GfxIndex index)
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}
    
void 
ResourceCommandEncoder::copyTexture(
    ITextureResource* dst,
    ResourceState dstState,
    SubresourceRange dstSubresource,
    ITextureResource::Offset3D dstOffset,
    ITextureResource* src,
    ResourceState srcState,
    SubresourceRange srcSubresource,
    ITextureResource::Offset3D srcOffset,
    ITextureResource::Extents extent
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}
    
void 
ResourceCommandEncoder::uploadTextureData(
    ITextureResource* dst,
    SubresourceRange subResourceRange,
    ITextureResource::Offset3D offset,
    ITextureResource::Extents extend,
    ITextureResource::SubresourceData* subResourceData,
    GfxCount subResourceDataCount
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}

void 
ResourceCommandEncoder::clearResourceView(
    IResourceView* view,
    ClearValue* clearValue,
    ClearResourceViewFlags::Enum flags
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}
    
void 
ResourceCommandEncoder::resolveResource(
    ITextureResource* source,
    ResourceState sourceState,
    SubresourceRange sourceRange,
    ITextureResource* dest,
    ResourceState destState,
    SubresourceRange destRange
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}
    
void 
ResourceCommandEncoder::resolveQuery(
    IQueryPool* queryPool,
    GfxIndex index,
    GfxCount count,
    IBufferResource* buffer,
    Offset offset
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}
    
void 
ResourceCommandEncoder::copyTextureToBuffer(
    IBufferResource* dst,
    Offset dstOffset,
    Size dstSize,
    Size dstRowStride,
    ITextureResource* src,
    ResourceState srcState,
    SubresourceRange srcSubresource,
    ITextureResource::Offset3D srcOffset,
    ITextureResource::Extents extent
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}
    
void 
ResourceCommandEncoder::textureSubresourceBarrier(
    ITextureResource* texture,
    SubresourceRange subresourceRange,
    ResourceState src,
    ResourceState dst
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}
    
void 
ResourceCommandEncoder::beginDebugEvent(const char* name, float rgbColor[3])
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}
    
void 
ResourceCommandEncoder::endDebugEvent()
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}
    
void*
ComputeCommandEncoder::getInterface(SlangUUID const& uuid)
{
    if (
        uuid == GUID::IID_IResourceCommandEncoder ||
        uuid == GUID::IID_IComputeCommandEncoder ||
        uuid == ISlangUnknown::getTypeGuid()
        )
    {
        return this;
    }
    return nullptr;
}

void
ComputeCommandEncoder::endEncoding()
{
    SLANG_RHI_UNREACHABLE("Not implemented");
}

Result
ComputeCommandEncoder::bindPipeline(
    IPipelineState* pipelineState, IShaderObject** outRootObject
    )
{
    return setPipelineStateImpl(pipelineState, outRootObject);
}

Result
ComputeCommandEncoder::bindPipelineWithRootObject(
    IPipelineState* pipelineState, IShaderObject* rootObject
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}


Result
ComputeCommandEncoder::dispatchCompute(int x, int y, int z)
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

Result
ComputeCommandEncoder::dispatchComputeIndirect(
    IBufferResource* argBuffer, Offset offset
    )
{
    SLANG_RHI_UNREACHABLE("Not implemented");
    return {};
}

} // namespace rhi::webgpu
