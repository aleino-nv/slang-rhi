#include "webgpu-shader-object-layout.h"

namespace rhi::webgpu {

Result ShaderObjectLayoutImpl::_init(Builder const* builder)
{
    auto renderer = builder->m_renderer;

    initBase(renderer, builder->m_session, builder->m_elementTypeLayout);
    
    m_bindingRanges = builder->m_bindingRanges;
    m_bufferRanges = builder->m_bufferRanges;
    m_textureRanges = builder->m_textureRanges;
    m_samplerRanges = builder->m_samplerRanges;

    m_bufferCount = builder->m_bufferCount;
    m_textureCount = builder->m_textureCount;
    m_samplerCount = builder->m_samplerCount;
    m_subObjectCount = builder->m_subObjectCount;
    m_subObjectRanges = builder->m_subObjectRanges;

    m_totalOrdinaryDataSize = builder->m_totalOrdinaryDataSize;

    m_containerType = builder->m_containerType;

    return SLANG_OK;
}
    
Result RootShaderObjectLayoutImpl::Builder::build(RootShaderObjectLayoutImpl** outLayout)
{
    RefPtr<RootShaderObjectLayoutImpl> layout = new RootShaderObjectLayoutImpl();
    SLANG_RETURN_ON_FAIL(layout->_init(this));

    returnRefPtrMove(outLayout, layout);
    return SLANG_OK;
}

Result ShaderObjectLayoutImpl::Builder::setElementTypeLayout(
    slang::TypeLayoutReflection* typeLayout
    )
{
    m_elementTypeLayout = typeLayout;
    return SLANG_OK;    
}

    
void RootShaderObjectLayoutImpl::Builder::addGlobalParams(slang::VariableLayoutReflection* globalsLayout)
{
    setElementTypeLayout(globalsLayout->getTypeLayout());
}

Result RootShaderObjectLayoutImpl::create(
    RendererBase* renderer,
    slang::IComponentType* program,
    slang::ProgramLayout* programLayout,
    RootShaderObjectLayoutImpl** outLayout
)
{
    RootShaderObjectLayoutImpl::Builder builder(renderer, program, programLayout);
    builder.addGlobalParams(programLayout->getGlobalParamsVarLayout());

    // TODO
    
    SLANG_RETURN_ON_FAIL(builder.build(outLayout));
    return SLANG_OK;
}

Result RootShaderObjectLayoutImpl::_init(Builder const* builder)
{
    SLANG_RETURN_ON_FAIL(Super::_init(builder));

    m_program = builder->m_program;
    m_programLayout = builder->m_programLayout;
    //m_entryPoints = builder->m_entryPoints;
    m_slangSession = m_program->getSession();

    return SLANG_OK;
}
    
} // namespace rhi::webgpu
