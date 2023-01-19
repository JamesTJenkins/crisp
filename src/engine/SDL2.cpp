#include "SDL2.hpp"
#include <iostream>

namespace Crisp::Core {
    SDL2::SDL2() {
        Initialize();
    }
    
    SDL2::~SDL2() {}

    void SDL2::Initialize() {
        SDL_Init(SDL_INIT_VIDEO);

        std::cout << "SDL2 Initialized." << std::endl;
    }

    int SDL2::PollEvent() {
        return SDL_PollEvent(&event);
    }

    SDL_Event SDL2::GetEvent() {
        return event;
    }

    // @brief Handles the previously polled event
    // @return returns 0 upon completing normal execution, 1 if a quit event was polled
    int SDL2::HandleEvent() {
        // Quit
        if (event.type == SDL_QUIT)
            return 1;

        return 0;
    }

    void SDL2::Cleanup() {
        SDL_Quit();

        std::cout << "SDL2 cleaned up." << std::endl;
    }
}