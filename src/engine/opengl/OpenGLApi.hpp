#pragma once
#include <SDL.h>

#include <vector>

#include "../IGraphicsApi.hpp"
#include "OpenGLMaterial.hpp"

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

        OpenGLShader& AddShader(ShaderImport& shader);
        OpenGLMaterial& AddMaterial(OpenGLShader* shader);
        void ClearScreen();
        void Draw();

        void Cleanup();

        std::vector<OpenGLShader> openGLShaders;
        std::vector<OpenGLMaterial> openGLMaterials;
    private:
        std::vector<OpenGLWindow> openGLWindows;
    };
}  // namespace Crisp::Core