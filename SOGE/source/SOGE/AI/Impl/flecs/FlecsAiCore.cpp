﻿#include "sogepch.hpp"

#include "SOGE/AI/Impl/flecs/FlecsAiCore.hpp"

#include "SOGE/Core/Timestep.hpp"


namespace soge
{
    FlecsAiCore::FlecsAiCore()
    {
        m_world.system("Hello World").kind(flecs::OnUpdate).run([](const flecs::iter& aIter) {
            SOGE_INFO_LOG("Hello World from flecs task with delta time of {}!", aIter.delta_time());
        });
    }

    void FlecsAiCore::Update()
    {
        (void)m_world.progress(Timestep::DeltaTime());
    }
}