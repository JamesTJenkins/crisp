#pragma once
#include <SDL.h>

namespace Crisp::Core {
    class SDL2 {
    public:
        SDL2();
        ~SDL2();

        void Initialize();
        int PollEvent();
        SDL_Event GetEvent();
        int HandleEvent();
        void Cleanup();
    private:
        SDL_Event event;
    };
}