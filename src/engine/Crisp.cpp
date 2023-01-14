#define SDL_MAIN_HANDLED
#include "Crisp.hpp"
#include "PackageManager.hpp"
// Packages
#include "SDL2.hpp"
#include "WindowManager.hpp"

using namespace Crisp::Core;

int main() {
    std::cout << "Initializing Crisp..." << std::endl;

    // Create package manager
    PackageManager packageManager;

    // Load sdl2
    std::shared_ptr<Feature> sdl = std::make_shared<SDL2>();
    packageManager.LoadFeature(sdl);
    // Load window manager
    std::shared_ptr<Feature> windowManager = std::make_shared<WindowManager>();
    packageManager.LoadFeature(windowManager);

    return 0;
}