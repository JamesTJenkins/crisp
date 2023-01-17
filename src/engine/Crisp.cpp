#define SDL_MAIN_HANDLED
#include "Crisp.hpp"
#include "PackageManager.hpp"
// Packages
#include "SDL2.hpp"
#include "WindowManager.hpp"
#include "opengl/OpenGLApi.hpp"

using namespace Crisp::Core;

int main() {
    std::cout << "Initializing Crisp..." << std::endl;

    // Load sdl2
    std::shared_ptr<SDL2> sdlSptr = std::make_shared<SDL2>();
    PackageManager::Get().LoadFeature(sdlSptr);
    SDL2* sdl2 = dynamic_cast<SDL2*>(sdlSptr.get());
    // Load OpenGL
    std::shared_ptr<OpenGLApi> openglSptr = std::make_shared<OpenGLApi>();
    PackageManager::Get().LoadFeature(openglSptr);
    // Load window manager
    std::shared_ptr<Feature> windowManagerSptr = std::make_shared<WindowManager>();
    PackageManager::Get().LoadFeature(windowManagerSptr);

    // Create window
    OpenGLApi* openGLApi = dynamic_cast<OpenGLApi*>(openglSptr.get());
    openGLApi->NewWindow("OpenGLTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400);

    bool running = true;
    while (running) {
        while (sdl2->PollEvent() != 0) {
            if (sdl2->HandleEvent() != 0)
                running = false;
        }

        //openGLApi->ClearScreen();
        //openGLApi->Draw();
    }

    return 0;
}