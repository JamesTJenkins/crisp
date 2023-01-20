#pragma once
#include <SDL.h>

#include <vector>

#include "../IGraphicsApi.hpp"
#include "OpenGLShader.hpp"

namespace Crisp::Core {
    struct OpenGLWindow {
        SDL_Window* window;
        SDL_GLContext gContext;

        OpenGLWindow(SDL_Window* _window) {
            window = _window;
        }
    };

    class OpenGLApi : public IGraphicsApi {
       public:
        OpenGLApi();
        ~OpenGLApi();

        void Initialize();
        bool NewWindow(const char* title, int x, int y, int width, int height);

        void AddShader(ShaderImport& shader);
        void ClearScreen();
        void Draw();

        void Cleanup();
       private:
        std::vector<OpenGLWindow> openGLWindows;
        std::vector<OpenGLShader> openGLShaders;
    };
}  // namespace Crisp::Core