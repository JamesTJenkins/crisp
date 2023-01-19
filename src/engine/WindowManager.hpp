#pragma once
#include <vector>
#include <SDL.h>

namespace Crisp::Core {
    class WindowManager {
    public:
        WindowManager();
        ~WindowManager();

        bool NewWindow(const char* title, int x, int y, int width, int height, uint32_t flags);
        int GetWindowCount();
        SDL_Window* GetWindow(int index);
        
        void Cleanup();
    private:
        std::vector<SDL_Window*> windows;
    };
}