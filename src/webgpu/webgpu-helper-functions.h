#pragma once

#include "webgpu-base.h"

namespace rhi::webgpu {

/// A "simple" binding offset that records an offset in buffer/texture/sampler slots
struct BindingOffset
{
    uint32_t buffer = 0;
    uint32_t texture = 0;
    uint32_t sampler = 0;

    /// Create a default (zero) offset
    BindingOffset() = default;

    /// Create an offset based on offset information in the given Slang `varLayout`
    BindingOffset(slang::VariableLayoutReflection* varLayout)
    {
        SLANG_RHI_UNREACHABLE("Not implemented");
    }

    /// Create an offset based on size/stride information in the given Slang `typeLayout`
    BindingOffset(slang::TypeLayoutReflection* typeLayout)
    {
        SLANG_RHI_UNREACHABLE("Not implemented");
    }

    /// Add any values in the given `offset`
    void operator+=(BindingOffset const& offset)
    {
        SLANG_RHI_UNREACHABLE("Not implemented");
    }
};

} // namespace rhi::webgpu
    
namespace rhi {

// Result SLANG_MCALL getWebGPUAdapters(std::vector<AdapterInfo>& outAdapters);
Result SLANG_MCALL createWebGPUDevice(const IDevice::Desc* desc, IDevice** outRenderer);

} // namespace rhi
