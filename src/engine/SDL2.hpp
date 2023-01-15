#pragma once
#include "Feature.hpp"
#include <SDL.h>

namespace Crisp::Core {
    class SDL2 : public Feature {
    public:
        SDL2();
        ~SDL2();

        void Initialize();
        int PollEvent();
        SDL_Event GetEvent();
        int HandleEvent();
        void Cleanup();
        int GetFeatureID();
    private:
        SDL_Event event;
    };
}