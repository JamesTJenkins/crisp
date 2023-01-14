#pragma once
#include <vector>
#include <SDL.h>
#include "Feature.hpp"

namespace Crisp::Core {
    class WindowManager : public Feature {
    public:
        WindowManager();
        ~WindowManager();

        bool CreateWindow(const char* title, int x, int y, int width, int height, uint32_t flags);
        void Cleanup();
        int GetFeatureID();
    
    private:
        std::vector<SDL_Window*> windows;
    };
}