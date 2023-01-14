#define SDL_MAIN_HANDLED
#include "Crisp.hpp"
#include "PackageManager.hpp"
// Packages
#include "SDL2.hpp"
#include "WindowManager.hpp"
//#include "Helper.hpp"

using namespace Crisp::Core;

int main() {
    std::cout << "Initializing Crisp..." << std::endl;

    PackageManager packageManager;

    // Load sdl2
    std::shared_ptr<SDL2> sdl = std::make_shared<SDL2>();
    packageManager.LoadFeature(sdl);
    // Load window manager
    std::shared_ptr<Feature> windowManager = std::make_shared<WindowManager>();
    packageManager.LoadFeature(windowManager);
    // Create window
    WindowManager* wm = dynamic_cast<WindowManager*>(windowManager.get());
    wm->CreateWindow("Test", 0, 0, 100, 100, 0);

    return 0;
}