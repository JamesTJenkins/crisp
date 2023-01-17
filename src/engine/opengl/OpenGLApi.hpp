#pragma once
#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <vector>
#include "../IGraphicsApi.hpp"

namespace Crisp::Core {
    struct OpenGLWindow {
        SDL_Window* window;
        SDL_GLContext gContext;

        OpenGLWindow(SDL_Window* _window) {
            window = _window;
        }
    };

    struct OpenGLShader {
        GLuint gProgramID;
        GLint gVertexPositionLocation;
    };

    class OpenGLApi : public IGraphicsApi {
    public:
        OpenGLApi();

        void Initialize();
        bool NewWindow(const char* title, int x, int y, int width, int height);

        void ClearScreen();
        void Draw();
        
        bool InitializeShader(ShaderImport& shader);

        void Cleanup();
        int GetFeatureID();
    private:
        void PrintShaderLog(GLuint shader);
        void PrintProgramLog(GLuint program);

        std::vector<OpenGLWindow> openGLWindows; 
        std::vector<OpenGLShader> openGLShaders;
        // Attribute for reflection i think
        GLint gVertexPos2DLocation = -1;
    };
}