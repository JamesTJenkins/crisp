#include "WindowManager.hpp"
#include "Helper.hpp"
#include "PackageManager.hpp"

namespace Crisp::Core {
    WindowManager::WindowManager() {}
    WindowManager::~WindowManager() {}

    bool WindowManager::CreateWindow(const char* title, int x, int y, int width, int height, uint32_t flags) {
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
        return true;
    }

    void WindowManager::Cleanup() {
        for (SDL_Window* i : windows) {
            SDL_DestroyWindow(i);
        }
        
        std::cout << "All windows cleaned up" << std::endl;
    }

    int WindowManager::GetFeatureID() {
        return GetStringHash("WindowManager");
    }
}