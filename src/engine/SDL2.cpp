#include "SDL2.hpp"
#include <SDL.h>
#include "Helper.hpp"

namespace Crisp::Core {
    SDL2::SDL2() {
        Initialize();
    }
    
    SDL2::~SDL2() {}

    void SDL2::Initialize() {
        SDL_Init(SDL_INIT_VIDEO);

        std::cout << "SDL2 Initialized." << std::endl;
    }

    void SDL2::Cleanup() {
        SDL_Quit();

        std::cout << "SDL2 cleaned up." << std::endl;
    }

    int SDL2::GetFeatureID() {
        return GetStringHash("SDL2");
    }
}