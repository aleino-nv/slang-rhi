#pragma once

#include "webgpu-base.h"
#include "webgpu-helper-functions.h"

namespace rhi::webgpu {

class ShaderObjectLayoutImpl : public ShaderObjectLayoutBase
{
public:
    // A shader object comprises three main kinds of state:
    //
    // * Zero or more bytes of ordinary ("uniform") data
    // * Zero or more *bindings* for textures, buffers, and samplers
    // * Zero or more *sub-objects* representing nested parameter blocks, etc.
    //
    // A shader object *layout* stores information that can be used to
    // organize these different kinds of state and optimize access to them.
    //
    // For example, both texture/buffer/sampler bindings and sub-objects
    // are organized into logical *binding ranges* by the Slang reflection
    // API, and a shader object layout will store information about those
    // ranges in a form that is usable for the Metal API:
    
    /// Information about a logical binding range as reported by Slang reflection
    struct BindingRangeInfo
    {
        /// The type of bindings in this range
        slang::BindingType bindingType;

        /// The number of bindings in this range
        Index count;

        /// The starting index for this range in the appropriate "flat" array in a
        /// shader object.
        /// E.g., for a buffers range, this would be an index into the `m_buffers` array.
        Index baseIndex;

        /// The offset of this binding range from the start of the sub-object.
        uint32_t registerOffset;

        /// An index into the sub-object array if this binding range is treated
        /// as a sub-object.
        Index subObjectIndex;

        /// TODO remove this once specialization is removed
        bool isSpecializable = false;
    };

    /// Offset information for a sub-object range
    struct SubObjectRangeOffset : BindingOffset
    {
        SubObjectRangeOffset() {}

        SubObjectRangeOffset(slang::VariableLayoutReflection* varLayout);

        /// The offset for "pending" ordinary data related to this range
        uint32_t pendingOrdinaryData = 0;
    };
    
    /// Stride information for a sub-object range
    struct SubObjectRangeStride : BindingOffset
    {
        SubObjectRangeStride() {}

        SubObjectRangeStride(slang::TypeLayoutReflection* typeLayout);

        /// The stride for "pending" ordinary data related to this range
        uint32_t pendingOrdinaryData = 0;
    };
    
    /// Information about a logical binding range as reported by Slang reflection
    struct SubObjectRangeInfo
    {
        /// The index of the binding range that corresponds to this sub-object range
        Index bindingRangeIndex;

        /// The layout expected for objects bound to this range (if known)
        RefPtr<ShaderObjectLayoutImpl> layout;

        /// The offset to use when binding the first object in this range
        SubObjectRangeOffset offset;

        /// Stride between consecutive objects in this range
        SubObjectRangeStride stride;
    };

    struct Builder
    {
    public:
        Builder(RendererBase* renderer, slang::ISession* session)
            : m_renderer(renderer)
            , m_session(session)
        {
        }

        RendererBase* m_renderer;
        slang::ISession* m_session;
        slang::TypeLayoutReflection* m_elementTypeLayout;

        std::vector<BindingRangeInfo> m_bindingRanges;
        std::vector<SubObjectRangeInfo> m_subObjectRanges;        

        /// The indices of the binding ranges that represent buffers
        std::vector<Index> m_bufferRanges;

        /// The indices of the binding ranges that represent textures
        std::vector<Index> m_textureRanges;

        /// The indices of the binding ranges that represent samplers
        std::vector<Index> m_samplerRanges;

        Index m_bufferCount = 0;
        Index m_textureCount = 0;
        Index m_samplerCount = 0;
        Index m_subObjectCount = 0;
        
        uint32_t m_totalOrdinaryDataSize = 0;

        /// The container type of this shader object. When `m_containerType` is
        /// `StructuredBuffer` or `Array`, this shader object represents a collection
        /// instead of a single object.
        ShaderObjectContainerType m_containerType = ShaderObjectContainerType::None;

        Result setElementTypeLayout(slang::TypeLayoutReflection* typeLayout);        

    };
    
    Index getBindingRangeCount()
    {
        SLANG_RHI_UNREACHABLE("Not implemented");
        return {};
    }
    
    BindingRangeInfo const& getBindingRange(Index index)
    {
        SLANG_RHI_UNREACHABLE("Not implemented");
        return {};
    }

    std::vector<SubObjectRangeInfo> const& getSubObjectRanges()
    {
        SLANG_RHI_UNREACHABLE("Not implemented");
        return {};
    }    

protected:

    std::vector<BindingRangeInfo> m_bindingRanges;
    std::vector<Index> m_bufferRanges;
    std::vector<Index> m_textureRanges;
    std::vector<Index> m_samplerRanges;
    Index m_bufferCount = 0;
    Index m_textureCount = 0;
    Index m_samplerCount = 0;
    Index m_subObjectCount = 0;
    uint32_t m_totalOrdinaryDataSize = 0;
    std::vector<SubObjectRangeInfo> m_subObjectRanges;    

    Result _init(Builder const* builder);
    
};
    
class RootShaderObjectLayoutImpl : public ShaderObjectLayoutImpl
{
    typedef ShaderObjectLayoutImpl Super;

public:

    struct Builder : Super::Builder
    {
        Builder(
            RendererBase* renderer,
            slang::IComponentType* program,
            slang::ProgramLayout* programLayout
        )
            : Super::Builder(renderer, program->getSession())
            , m_program(program)
            , m_programLayout(programLayout)
        {
        }

        Result build(RootShaderObjectLayoutImpl** outLayout);
        void addGlobalParams(slang::VariableLayoutReflection* globalsLayout);

        slang::IComponentType* m_program;
        slang::ProgramLayout* m_programLayout;
    };

    static Result create(
        RendererBase* renderer,
        slang::IComponentType* program,
        slang::ProgramLayout* programLayout,
        RootShaderObjectLayoutImpl** outLayout
    );

protected:

    Result _init(Builder const* builder);

    ComPtr<slang::IComponentType> m_program;
    slang::ProgramLayout* m_programLayout = nullptr;

    //std::vector<EntryPointInfo> m_entryPoints;    
    
};
    
} // namespace rhi::webgpu
