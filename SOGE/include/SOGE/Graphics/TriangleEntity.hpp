﻿#ifndef SOGE_GRAPHICS_TRIANGLEENTITY_HPP
#define SOGE_GRAPHICS_TRIANGLEENTITY_HPP

#include "SOGE/DI/Dependency.hpp"
#include "SOGE/Graphics/GraphicsEntity.hpp"
#include "SOGE/Graphics/TriangleGraphicsPipeline.hpp"

#include <EASTL/span.h>


namespace soge
{
    class TriangleEntity : public GraphicsEntity
    {
    private:
        using ConstantBuffer = TriangleGraphicsPipeline::ConstantBuffer;

        eastl::reference_wrapper<GraphicsCore> m_core;
        eastl::reference_wrapper<TriangleGraphicsPipeline> m_pipeline;

        Transform m_transform;

        nvrhi::BufferHandle m_nvrhiConstantBuffer;
        nvrhi::BufferHandle m_nvrhiVertexBuffer;
        nvrhi::BufferHandle m_nvrhiIndexBuffer;
        nvrhi::BindingSetHandle m_nvrhiBindingSet;

    public:
        using Vertex = TriangleGraphicsPipeline::Vertex;
        using Vertices = eastl::span<const Vertex>;

        using Index = std::uint32_t;
        using Indices = eastl::span<const Index>;

        explicit TriangleEntity(GraphicsCore& aCore, TriangleGraphicsPipeline& aPipeline);

        [[nodiscard]]
        Transform& GetTransform();
        [[nodiscard]]
        const Transform& GetTransform() const;

        void UpdateVertices(Vertices aVertices);
        void UpdateIndices(Indices aIndices);

        [[nodiscard]]
        nvrhi::CommandListHandle Update(const nvrhi::Viewport& aViewport, const Camera& aCamera,
                                        GraphicsRenderPass& aRenderPass, GraphicsPipeline& aPipeline) override;
    };
}

SOGE_DI_REGISTER_NS(soge, TriangleEntity, df::Factory<TriangleEntity, GraphicsCore, TriangleGraphicsPipeline>)

#endif // SOGE_GRAPHICS_TRIANGLEENTITY_HPP
