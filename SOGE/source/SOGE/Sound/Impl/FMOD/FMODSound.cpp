#include "sogepch.hpp"
#include "SOGE/Sound/Impl/FMOD/FMODSound.hpp"
#include "SOGE/Sound/Impl/FMOD/FMODConfig.hpp"
#include "SOGE/Sound/Impl/FMOD/FMODException.hpp"


namespace soge
{
    FMODSound::FMODSound(SoundResource& aSoundResource) : m_fmodSound(nullptr), m_soundResource(aSoundResource)
    {
    }

    FMODSound::FMODSound(FMOD::Sound* aFMODSound, SoundResource& aSoundResource)
        : m_fmodSound(aFMODSound), m_soundResource(aSoundResource)
    {
    }

    FMODSound::~FMODSound()
    {
        m_fmodSound->release();
    }

    bool FMODSound::Load(FMOD::System* aFMODSystem, const FMODConfig& aFMODConfig)
    {
        if (!m_soundResource.IsLoaded())
        {
            FMOD_MODE dimMode = m_soundResource.Is3D() ? FMOD_3D : FMOD_2D;
            FMOD_MODE loopMode = m_soundResource.IsLooping() ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
            SOGE_WARN_LOG("Loop mode: {}", m_soundResource.IsLooping());

            FMODThrowIfFailed(
                aFMODSystem->createSound(m_soundResource.GetFullPath().c_str(), dimMode, nullptr, &m_fmodSound));
            FMODThrowIfFailed(m_fmodSound->setMode(loopMode));

            if (dimMode == FMOD_3D)
                FMODThrowIfFailed(m_fmodSound->set3DMinMaxDistance(0.5f * aFMODConfig.GetDistanceFactor(),
                                                                   5000.0f * aFMODConfig.GetDistanceFactor()));

            return true;
        }
        SOGE_WARN_LOG("Sound resource {} already loaded!", m_soundResource.GetName().c_str());
        return false;
    }

    bool FMODSound::Reload(FMOD::System* aFMODSystem, const FMODConfig& aFMODConfig)
    {
        return false;
    }

    bool FMODSound::Unload(FMOD::System* aFMODSystem)
    {
        return false;
    }

    FMOD::Sound* FMODSound::GetSound() const
    {
        return m_fmodSound;
    }
}
