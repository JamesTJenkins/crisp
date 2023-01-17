#pragma once
#include <vector>
#include <SDL.h>
#include "Feature.hpp"

namespace Crisp::Core {
    class WindowManager : public Feature {
    public:
        WindowManager();
        ~WindowManager();

        bool NewWindow(const char* title, int x, int y, int width, int height, uint32_t flags);
        int GetWindowCount();
        SDL_Window* GetWindow(int index);
        
        void Cleanup();
        int GetFeatureID();
    private:
        std::vector<SDL_Window*> windows;
    };
}