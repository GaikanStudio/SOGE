#ifndef SOGE_GRAPHICS_GRAPHICSMODULE_HPP
#define SOGE_GRAPHICS_GRAPHICSMODULE_HPP

#include "SOGE/Core/Module.hpp"
#include "SOGE/Graphics/CameraManager.hpp"
#include "SOGE/Graphics/GraphicsCore.hpp"
#include "SOGE/Graphics/GraphicsEntityManager.hpp"
#include "SOGE/Graphics/RenderGraph.hpp"
#include "SOGE/Graphics/ViewportManager.hpp"


namespace soge
{
    class GraphicsModule : public Module
    {
    private:
        CameraManager m_cameraManager;
        ViewportManager m_viewportManager;
        GraphicsEntityManager m_entityManager;

        GraphicsCore* m_graphicsCore;
        RenderGraph* m_renderGraph;

    public:
        explicit GraphicsModule();

        virtual void SetRenderTarget(const Window& aWindow);
        virtual void SetRenderGraph(RenderGraph& aRenderGraph);

        virtual void Update();

        [[nodiscard]]
        GraphicsEntityManager& GetEntityManager() noexcept;
        [[nodiscard]]
        CameraManager& GetCameraManager() noexcept;
        [[nodiscard]]
        ViewportManager& GetViewportManager() noexcept;

        void Load(di::Container& aContainer, ModuleManager& aModuleManager) override;
        void Unload(di::Container& aContainer, ModuleManager& aModuleManager) override;
    };
}

SOGE_DI_REGISTER_MODULE_NS(soge, GraphicsModule)

#endif // SOGE_GRAPHICS_GRAPHICSMODULE_HPP
