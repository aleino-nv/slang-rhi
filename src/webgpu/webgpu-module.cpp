#include "webgpu-module.h"

#include "core/assert.h"

#if SLANG_WINDOWS_FAMILY
#include <windows.h>
#endif

namespace rhi::webgpu {
    
Result WebGPUModule::init()
{

    HMODULE module = {};
#if SLANG_WINDOWS_FAMILY
    module = ::LoadLibraryA("webgpu_dawn.dll");
#else
    module = {};
#endif

    if (!module)
    {
        return SLANG_FAIL;
    }

    m_module = (void*)module;
    return SLANG_OK;
}

void* WebGPUModule::getFunction(const char* name) const
{
    if (!m_module)
    {
        SLANG_RHI_UNREACHABLE("Module not initialized");
        return nullptr;
    }
#if SLANG_WINDOWS_FAMILY
    return ::GetProcAddress((HMODULE)m_module, name);
#else
    return nullptr;
#endif
}

void WebGPUModule::destroy()
{
    if (m_module)
    {
#if SLANG_WINDOWS_FAMILY
        ::FreeLibrary((HMODULE)m_module);
#else
        SLANG_RHI_ASSERT(m_module == nullptr);
#endif
        m_module = nullptr;
    }
}

} // namespace rhi::webgpu
