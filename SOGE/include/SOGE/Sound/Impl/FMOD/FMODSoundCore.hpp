#ifndef SOGE_SOUND_IMPL_FMOD_FMODSOUNDCORE_HPP
#define SOGE_SOUND_IMPL_FMOD_FMODSOUNDCORE_HPP

#include "SOGE/Sound/SoundCore.hpp"
#include "SOGE/Sound/Impl/FMOD/FMODSound.hpp"
#include "SOGE/Sound/Impl/FMOD/FMODConfig.hpp"
#include "SOGE/Sound/Impl/FMOD/FMODListener.hpp"
#include "SOGE/Sound/Impl/FMOD/FMODSoundChannel.hpp"

#include <FMOD/fmod.hpp>
#include <FMOD/fmod_studio.hpp>


namespace soge
{
    class FMODSoundCore : public SoundCore
    {
    private:
        FMODConfig m_config;
        FMODListener m_listener;

        FMOD::System* m_fmodSystem;
        FMOD::Studio::System* m_fmodStudioSystem;

        FMODSoundChannel* m_defaultSoundChannel;
        eastl::map<UUIDv4::UUID, FMODSound*> m_loadedSounds;

    public:
        explicit FMODSoundCore(EventModule& aEventModule);
        ~FMODSoundCore();

        void Update() override;
        void Update3DListener(const glm::vec3& aPos,
                              const glm::vec3& aForwardVec,
                              const glm::vec3& aUpwardVec) override;

        void LoadSoundResource(SoundResource& aSoundResource) override;
        void PlaySoundResource(SoundResource& aSoundResource) override;
        void PauseSoundResource(SoundResource& aSoundResource) override;
        void UnpauseSoundResource(SoundResource& aSoundResource) override;
        void StopSoundResource(SoundResource& aSoundResource) override;
        bool IsSoundResourcePlaying(SoundResource& aSoundResource) override;
    };

    using ImplSoundCore = soge::FMODSoundCore;
}

SOGE_DI_REGISTER_NS(soge, FMODSoundCore, df::Single<FMODSoundCore, EventModule>, tag::Overrides<SoundCore>)

#endif // !SOGE_SOUND_IMPL_FMOD_FMODSOUNDCORE_HPP
