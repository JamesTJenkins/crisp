#include "WindowManager.hpp"
#include <iostream>

namespace Crisp::Core {
    WindowManager::WindowManager() {}
    
    WindowManager::~WindowManager() {}

    bool WindowManager::NewWindow(const char* title, int x, int y, int width, int height, uint32_t flags) {
        // Attempt to create window
        SDL_Window* window = SDL_CreateWindow(
            title,
            x,
            y,
            width,
            height,
            flags
        );

        // If fail
        if (window == NULL) {
            std::cout << "Failed to create window" << std::endl;
            return false;
        }

        // If succeed add to vector and return true
        windows.push_back(window);
        std::cout << "Window Created" << std::endl;
        return true;
    }

    int WindowManager::GetWindowCount() {
        return windows.size();
    }

    SDL_Window* WindowManager::GetWindow(int index) {
        return windows[index];
    }

    void WindowManager::Cleanup() {
        for (SDL_Window* i : windows) {
            SDL_DestroyWindow(i);
        }
        
        std::cout << "All windows cleaned up" << std::endl;
    }
}