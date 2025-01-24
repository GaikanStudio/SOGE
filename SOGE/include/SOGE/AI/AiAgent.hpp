﻿#ifndef SOGE_AI_AIAGENT_HPP
#define SOGE_AI_AIAGENT_HPP

#include <flecs.h>
#include <flecs/addons/cpp/entity.hpp>


namespace soge
{
    class AiAgent
    {
    private:
        friend class AiModule;

        explicit AiAgent(flecs::entity aEntity);

        flecs::entity m_entity;

    public:
        [[nodiscard]]
        flecs::entity GetEntity() const;

        [[nodiscard]]
        eastl::string_view GetName() const;
        void SetName(eastl::string_view aName);

        bool operator==(const AiAgent& aOther) const;
    };
}

#endif // SOGE_AI_AIAGENT_HPP
