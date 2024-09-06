#pragma once

#include "webgpu-base.h"

namespace rhi::webgpu {

class DeviceImpl : public RendererBase
{
public:

    Result initWebGPUInstanceAndAdapterAndDevice();
    
    virtual SLANG_NO_THROW Result SLANG_MCALL
        initialize(const Desc& desc) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        createTransientResourceHeap(
            const rhi::ITransientResourceHeap::Desc &,
            rhi::ITransientResourceHeap **
        ) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        createTextureResource(
            const rhi::ITextureResource::Desc &,
            const rhi::ITextureResource::SubresourceData *,
            rhi::ITextureResource **
        ) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        createBufferResource(
            const rhi::IBufferResource::Desc &,
            const void *,
            rhi::IBufferResource **
        ) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        createSamplerState(
            const rhi::ISamplerState::Desc &,
            rhi::ISamplerState **
        ) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        createTextureView(
            rhi::ITextureResource *,
            const rhi::IResourceView::Desc &,
            rhi::IResourceView **
        ) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        createBufferView(
            rhi::IBufferResource *,
            rhi::IBufferResource *,
            const rhi::IResourceView::Desc &,
            rhi::IResourceView **
        ) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        createFramebufferLayout(
            const rhi::IFramebufferLayout::Desc &,
            rhi::IFramebufferLayout **
        ) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        createFramebuffer(
            const rhi::IFramebuffer::Desc &,
            rhi::IFramebuffer **
        ) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        createRenderPassLayout(
            const rhi::IRenderPassLayout::Desc &,
            rhi::IRenderPassLayout **
        ) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        createSwapchain(
            const rhi::ISwapchain::Desc &,
            rhi::WindowHandle,
            rhi::ISwapchain **
        ) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        createInputLayout(
            const rhi::IInputLayout::Desc &,
            rhi::IInputLayout **
        ) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        createCommandQueue(
            const rhi::ICommandQueue::Desc &,
            rhi::ICommandQueue **
        ) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        createProgram(
            const rhi::IShaderProgram::Desc &,
            rhi::IShaderProgram **,
            ISlangBlob **
        ) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        createGraphicsPipelineState(
            const rhi::GraphicsPipelineStateDesc &,
            rhi::IPipelineState **
        ) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        createComputePipelineState(
            const rhi::ComputePipelineStateDesc &,
            rhi::IPipelineState **
        ) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        createQueryPool(
            const rhi::IQueryPool::Desc &,
            rhi::IQueryPool **
        ) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        createShaderObject(
            rhi::ShaderObjectLayoutBase *,
            rhi::IShaderObject **
        ) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        createMutableShaderObject(
            rhi::ShaderObjectLayoutBase *,
            rhi::IShaderObject **
        ) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        createShaderObjectLayout(
            slang::ISession *,
            slang::TypeLayoutReflection *,
            rhi::ShaderObjectLayoutBase **
        ) override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        readTextureResource(
            rhi::ITextureResource *,
            rhi::ResourceState,
            ISlangBlob **,
            rhi::Size *,
            rhi::Size *
        );

    virtual SLANG_NO_THROW Result SLANG_MCALL
        readBufferResource(
            rhi::IBufferResource *,
            rhi::Offset,
            rhi::Size,
            ISlangBlob **
        );

    virtual SLANG_NO_THROW const DeviceInfo& SLANG_MCALL
        getDeviceInfo() const override;

    ~DeviceImpl();

    WebGPUApi m_api;

    uint32_t m_queueAllocCount;

private:
    
    DeviceInfo m_info;
    Desc m_desc;    

    WebGPUModule m_module;
	WGPUAdapter m_adapter;
	WGPUDevice m_device;


};

} // namespace rhi::webgpu
