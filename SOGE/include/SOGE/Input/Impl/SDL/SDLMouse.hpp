#ifndef SOGE_INPUT_IMPL_SDL_SDLMOUSE_HPP
#define SOGE_INPUT_IMPL_SDL_SDLMOUSE_HPP

#include "SOGE/Input/Device/Mouse.hpp"
#include "SOGE/Input/Impl/SDL/SDLInputCore.hpp"
#include "SOGE/Input/InputTypes.hpp"


namespace soge
{
    class SDLMouse final : public Mouse
    {
    private:
        SharedPtr<SDLInputCore> m_inputCoreSDL;
        std::uint32_t m_repeatCounter;

    public:
        explicit SDLMouse(const SharedPtr<SDLInputCore>& aInputCore);

        void Update() override;

        bool IsButtonPressed(Key aMouseButton) override;
        bool IsButtonReleased(Key aMouseButton) override;
    };

    typedef SDLMouse ImplMouse;
}

#endif // SOGE_INPUT_IMPL_SDL_SDLMOUSE_HPP
