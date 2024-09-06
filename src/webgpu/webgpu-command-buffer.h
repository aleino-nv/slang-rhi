#pragma once

#include "webgpu-base.h"
#include "webgpu-command-encoder.h"
#include "webgpu-shader-object.h"

namespace rhi::webgpu {

class DeviceImpl;
class TransientResourceHeapImpl;
class ComputeCommandEncoder;

class CommandBufferImpl : public ICommandBuffer, public ComObject
{
public:
    SLANG_COM_OBJECT_IUNKNOWN_ALL
    ICommandBuffer* getInterface(const Guid& guid);

    Result init(DeviceImpl* device, TransientResourceHeapImpl* transientHeap);

public:

    RootShaderObjectImpl m_rootObject;    

    RefPtr<ComputeCommandEncoder> m_computeCommandEncoder;

public:

    virtual SLANG_NO_THROW void SLANG_MCALL
        encodeRenderCommands(
            IRenderPassLayout* renderPass,
            IFramebuffer* framebuffer,
            IRenderCommandEncoder** outEncoder
        ) override;

    virtual SLANG_NO_THROW void SLANG_MCALL
        encodeComputeCommands(IComputeCommandEncoder** outEncoder) override;

    virtual SLANG_NO_THROW void SLANG_MCALL
        encodeResourceCommands(IResourceCommandEncoder** outEncoder) override;

    virtual SLANG_NO_THROW void SLANG_MCALL
        encodeRayTracingCommands(IRayTracingCommandEncoder** outEncoder) override;

    virtual SLANG_NO_THROW void SLANG_MCALL
        close() override;

    virtual SLANG_NO_THROW Result SLANG_MCALL
        getNativeHandle(InteropHandle* outHandle) override;

};

} // namespace rhi::webgpu
