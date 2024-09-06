#pragma once

#include <slang-rhi.h>
#define WGPU_SKIP_DECLARATIONS
#include <webgpu.h>

namespace rhi::webgpu {

struct WebGPUModule
{
    void* getFunction(const char* name) const;

    Result init();
    void destroy();

    ~WebGPUModule() { destroy(); }

private:

    void* m_module = nullptr;

};

} // namespace rhi::webgpu
