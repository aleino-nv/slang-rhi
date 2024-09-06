#pragma once

#include "webgpu-base.h"
#include "webgpu-pipeline-state.h"

namespace rhi::webgpu {

class CommandBufferImpl;

class PipelineCommandEncoder : public ComObject
{

public:
    CommandBufferImpl* m_commandBuffer;
    RefPtr<PipelineStateImpl> m_currentPipeline;
    
    void init(CommandBufferImpl* commandBuffer);

    Result setPipelineStateImpl(IPipelineState* state, IShaderObject** outRootObject);    

};

class ResourceCommandEncoder :
    public IResourceCommandEncoder, public PipelineCommandEncoder
{
public:

    virtual void* getInterface(SlangUUID const& guid);

    virtual SLANG_NO_THROW Result SLANG_MCALL
        queryInterface(SlangUUID const& uuid, void** outObject) override;

    virtual SLANG_NO_THROW uint32_t SLANG_MCALL
        addRef() override { return 1; }

    virtual SLANG_NO_THROW uint32_t SLANG_MCALL
        release() override { return 1; }

    virtual SLANG_NO_THROW void SLANG_MCALL
        copyBuffer(
            IBufferResource* dst,
            Offset dstOffset,
            IBufferResource* src,
            Offset srcOffset,
            Size size
        ) override;

    virtual SLANG_NO_THROW void SLANG_MCALL
        uploadBufferData(
            IBufferResource* buffer, Offset offset, Size size, void* data
        ) override;

    virtual SLANG_NO_THROW void SLANG_MCALL
        textureBarrier(
            GfxCount count,
            ITextureResource* const* textures,
            ResourceState src,
            ResourceState dst
        ) override;

    virtual SLANG_NO_THROW void SLANG_MCALL
        bufferBarrier(
            GfxCount count,
            IBufferResource* const* buffers,
            ResourceState src,
            ResourceState dst
        ) override;

    virtual SLANG_NO_THROW void SLANG_MCALL
        endEncoding() override;

    virtual SLANG_NO_THROW void SLANG_MCALL
        writeTimestamp(IQueryPool* queryPool, GfxIndex index) override;

    virtual SLANG_NO_THROW void SLANG_MCALL
        copyTexture(
            ITextureResource* dst,
            ResourceState dstState,
            SubresourceRange dstSubresource,
            ITextureResource::Offset3D dstOffset,
            ITextureResource* src,
            ResourceState srcState,
            SubresourceRange srcSubresource,
            ITextureResource::Offset3D srcOffset,
            ITextureResource::Extents extent
        ) override;

    virtual SLANG_NO_THROW void SLANG_MCALL
        uploadTextureData(
            ITextureResource* dst,
            SubresourceRange subResourceRange,
            ITextureResource::Offset3D offset,
            ITextureResource::Extents extend,
            ITextureResource::SubresourceData* subResourceData,
            GfxCount subResourceDataCount
        ) override;

    virtual SLANG_NO_THROW void SLANG_MCALL
        clearResourceView(
            IResourceView* view,
            ClearValue* clearValue,
            ClearResourceViewFlags::Enum flags
        ) override;

    virtual SLANG_NO_THROW void SLANG_MCALL
        resolveResource(
            ITextureResource* source,
            ResourceState sourceState,
            SubresourceRange sourceRange,
            ITextureResource* dest,
            ResourceState destState,
            SubresourceRange destRange
        ) override;

    virtual SLANG_NO_THROW void SLANG_MCALL
        resolveQuery(
            IQueryPool* queryPool,
            GfxIndex index,
            GfxCount count,
            IBufferResource* buffer,
            Offset offset
        ) override;

    virtual SLANG_NO_THROW void SLANG_MCALL
        copyTextureToBuffer(
            IBufferResource* dst,
            Offset dstOffset,
            Size dstSize,
            Size dstRowStride,
            ITextureResource* src,
            ResourceState srcState,
            SubresourceRange srcSubresource,
            ITextureResource::Offset3D srcOffset,
            ITextureResource::Extents extent
        ) override;

    virtual SLANG_NO_THROW void SLANG_MCALL
        textureSubresourceBarrier(
            ITextureResource* texture,
            SubresourceRange subresourceRange,
            ResourceState src,
            ResourceState dst
        ) override;

    virtual SLANG_NO_THROW void SLANG_MCALL
        beginDebugEvent(const char* name, float rgbColor[3]) override;

    virtual SLANG_NO_THROW void SLANG_MCALL
        endDebugEvent() override;

};

class ComputeCommandEncoder :
    public IComputeCommandEncoder, public ResourceCommandEncoder
{

public:
    SLANG_RHI_FORWARD_RESOURCE_COMMAND_ENCODER_IMPL(ResourceCommandEncoder)

    virtual void*
        getInterface(SlangUUID const& uuid) override;

    virtual SLANG_NO_THROW void SLANG_MCALL
        endEncoding() override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        bindPipeline(
            IPipelineState* pipelineState, IShaderObject** outRootObject
        ) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        bindPipelineWithRootObject(
            IPipelineState* pipelineState, IShaderObject* rootObject
        ) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        dispatchCompute(int x, int y, int z) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        dispatchComputeIndirect(IBufferResource* argBuffer, Offset offset) override;

};

} // namespace rhi::webgpu
