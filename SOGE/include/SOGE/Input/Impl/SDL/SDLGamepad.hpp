#ifndef SOGE_INPUT_IMPL_SDL_SDLGAMEPAD_HPP
#define SOGE_INPUT_IMPL_SDL_SDLGAMEPAD_HPP

#include "SOGE/Input/Device/Gamepad.hpp"
#include "SOGE/Input/Impl/SDL/SDLInputCore.hpp"
#include "SOGE/Input/InputTypes.hpp"


namespace soge
{
    class SDLGamepad final : public Gamepad
    {
    private:
        SharedPtr<SDLInputCore> m_inputCoreSDL;

    public:
        explicit SDLGamepad(const SharedPtr<SDLInputCore>& aInputCore);
    };

    typedef SDLGamepad ImplGamepad;
}

#endif // SOGE_INPUT_IMPL_SDL_SDLGAMEPAD_HPP
