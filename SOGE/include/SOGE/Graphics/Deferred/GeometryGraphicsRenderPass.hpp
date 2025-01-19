﻿#ifndef SOGE_GRAPHICS_DEFERRED_GEOMETRYGRAPHICSRENDERPASS_HPP
#define SOGE_GRAPHICS_DEFERRED_GEOMETRYGRAPHICSRENDERPASS_HPP

#include "SOGE/Graphics/GraphicsCore.hpp"
#include "SOGE/Graphics/GraphicsRenderPass.hpp"


namespace soge
{
    class GeometryGraphicsRenderPass : public GraphicsRenderPass
    {
    private:
        eastl::reference_wrapper<GraphicsCore> m_core;

        nvrhi::FramebufferHandle m_nvrhiFramebuffer;
        nvrhi::TextureHandle m_nvrhiNormalTexture;
        nvrhi::TextureHandle m_nvrhiAlbedoTexture;

    public:
        explicit GeometryGraphicsRenderPass(GraphicsCore& aCore);

        void ClearFramebuffer(nvrhi::ICommandList& aCommandList);

        [[nodiscard]]
        nvrhi::ITexture& GetAlbedoTexture();
        [[nodiscard]]
        nvrhi::ITexture& GetNormalTexture();

        [[nodiscard]]
        nvrhi::IFramebuffer& GetFramebuffer() override;
    };
}

SOGE_DI_REGISTER_NS(soge, GeometryGraphicsRenderPass, df::Single<GeometryGraphicsRenderPass, GraphicsCore>)

#endif // SOGE_GRAPHICS_DEFERRED_GEOMETRYGRAPHICSRENDERPASS_HPP
