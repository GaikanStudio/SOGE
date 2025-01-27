﻿#include "sogepch.hpp"

#include "SOGE/Graphics/Deferred/DeferredRenderGraph.hpp"

#include "SOGE/Graphics/GraphicsEntity.hpp"
#include "SOGE/Graphics/Utils/GraphicsCommandListGuard.hpp"


namespace soge
{
    DeferredRenderGraph::DeferredRenderGraph(GraphicsCore& aCore, GeometryGraphicsRenderPass& aGeometryPass,
                                             FinalGraphicsRenderPass& aFinalPass,
                                             GeometryGraphicsPipeline& aGeometryPipeline,
                                             AmbientLightGraphicsPipeline& aAmbientLightPipeline,
                                             DirectionalLightGraphicsPipeline& aDirectionalLightPipeline,
                                             PointLightGraphicsPipeline& aPointLightPipeline)
        : RenderGraph{aCore}, m_core{aCore}, m_geometryPass{aGeometryPass}, m_finalPass{aFinalPass},
          m_geometryPipeline{aGeometryPipeline}, m_ambientLightPipeline{aAmbientLightPipeline},
          m_directionalLightPipeline{aDirectionalLightPipeline}, m_pointLightPipeline{aPointLightPipeline}
    {
    }

    void DeferredRenderGraph::Execute(const nvrhi::Viewport& aViewport, const Camera& aCamera, const Entities aEntities)
    {
        GraphicsCore& core = m_core;
        nvrhi::IDevice& device = core.GetRawDevice();

        GeometryGraphicsRenderPass& geometryPass = m_geometryPass;
        GeometryGraphicsPipeline& geometryPipeline = m_geometryPipeline;

        FinalGraphicsRenderPass& finalPass = m_finalPass;
        AmbientLightGraphicsPipeline& ambientLightPipeline = m_ambientLightPipeline;
        DirectionalLightGraphicsPipeline& directionalLightPipeline = m_directionalLightPipeline;
        PointLightGraphicsPipeline& pointLightPipeline = m_pointLightPipeline;

        nvrhi::CommandListParameters commandListDesc{};
        commandListDesc.enableImmediateExecution = false;

        const nvrhi::CommandListHandle commandList = device.createCommandList(commandListDesc);
        {
            GraphicsCommandListGuard commandListGuard{*commandList};

            for (auto&& entity : aEntities)
            {
                entity.get().WriteResources(commandListGuard);
            }

            geometryPass.ClearFramebuffer(commandListGuard);
            geometryPipeline.WriteConstantBuffer(aCamera, commandListGuard);
            for (auto&& entityRef : aEntities)
            {
                if (const auto entity = dynamic_cast<GeometryGraphicsPipeline::Entity*>(&entityRef.get()))
                {
                    geometryPipeline.Execute(aViewport, aCamera, *entity, commandListGuard);
                }
            }

            finalPass.ClearFramebuffer(commandListGuard);
            {
                const auto destDepthTexture = finalPass.GetFramebuffer().getDesc().depthAttachment.texture;
                const auto srcDepthTexture = geometryPass.GetFramebuffer().getDesc().depthAttachment.texture;
                commandListGuard->copyTexture(destDepthTexture, {}, srcDepthTexture, {});
            }

            directionalLightPipeline.WriteConstantBuffer(aCamera, commandListGuard);
            pointLightPipeline.WriteConstantBuffer(aCamera, commandListGuard);
            for (auto&& entityRef : aEntities)
            {
                if (const auto entity = dynamic_cast<AmbientLightGraphicsPipeline::Entity*>(&entityRef.get()))
                {
                    ambientLightPipeline.Execute(aViewport, aCamera, *entity, commandListGuard);
                }
                if (const auto entity = dynamic_cast<DirectionalLightGraphicsPipeline::Entity*>(&entityRef.get()))
                {
                    directionalLightPipeline.Execute(aViewport, aCamera, *entity, commandListGuard);
                }
                if (const auto entity = dynamic_cast<PointLightGraphicsPipeline::Entity*>(&entityRef.get()))
                {
                    pointLightPipeline.Execute(aViewport, aCamera, *entity, commandListGuard);
                }
            }
        }
        core.ExecuteCommandList(commandList, nvrhi::CommandQueue::Graphics);
    }
}
