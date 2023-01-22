#include "OpenGLApi.hpp"

#include <gl/glu.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "../FeatureManager.hpp"
#include "../WindowManager.hpp"
#include "../components/Camera.hpp"

namespace Crisp::Core {
    OpenGLApi::OpenGLApi() {}
    OpenGLApi::~OpenGLApi() {}

    // OpenGL initializes on window creation
    void OpenGLApi::Initialize() {}

    bool OpenGLApi::NewWindow(const char *title, int x, int y, int width, int height) {
        bool success = true;

        // Create window in window manager
        WindowManager *wm = FeatureManager::Get().GetFeature<WindowManager>();
        if (wm->NewWindow(title, x, y, width, height, SDL_WINDOW_OPENGL)) {
            // Get window
            SDL_Window *window = wm->GetWindow(wm->GetWindowCount() - 1);
            // Link to context
            OpenGLWindow openGLWindow(window);
            openGLWindows.push_back(openGLWindow);
        
            // OpenGL 3.1 core
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

            // Init glew
            openGLWindow.gContext = SDL_GL_CreateContext(openGLWindow.window);
            if (openGLWindow.gContext == NULL) {
                std::cout << "OpenGL context cound not be created. SDL Error: " << SDL_GetError() << std::endl;
                success = false;
            } else {
                glewExperimental = GL_TRUE;
                GLenum glewError = glewInit();
                if (glewError != GLEW_OK)
                    std::cout << "Error initializing glew. SDL Error: " << glewGetErrorString(glewError) << std::endl;

                // Vsync
                if (SDL_GL_SetSwapInterval(1) < 0)
                    std::cout << "Unable to set vsync. SDL Error: " << SDL_GetError() << std::endl;
            }

            std::cout << "Initialized opengl" << std::endl;
        } else {
            success = false;
        }

        return success;
    }

    OpenGLShader& OpenGLApi::AddShader(ShaderImport& shader) {
        OpenGLShader newShader(shader);
        openGLShaders.push_back(newShader);
        return openGLShaders[openGLShaders.size() - 1];
    }

    OpenGLMaterial& OpenGLApi::AddMaterial(OpenGLShader* shader) {
        OpenGLMaterial newMat(shader);
        openGLMaterials.push_back(newMat);
        return openGLMaterials[openGLMaterials.size() - 1];
    }

    void OpenGLApi::ClearScreen() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    void OpenGLApi::Draw() {
        ClearScreen();
        
        // Get current camera rendering to screen
        Camera* mainCamera = Camera::GetMainCamera();
        // Check camera was successfully got
        if (mainCamera == nullptr) {
            std::cout << "No camera is set to render" << std::endl;
            return;
        }

        // TEST
        glBegin(GL_QUADS);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(-0.5f, 0.5f);
        glEnd();
        // ENDTEST

        // SHADER REFLECTION

        for (OpenGLShader shader : openGLShaders) {
            int maxLength;
            glGetProgramiv(shader.programID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);
            char* name = new char[maxLength + 1]; // Size should be allocated to be maxLength + 1

            int uniformCount;
            glGetProgramiv(shader.programID, GL_ACTIVE_UNIFORMS, &uniformCount);

            for (int i = 0; i < uniformCount; i++) {
                GLint size;
                GLenum type;
                glGetActiveUniform(shader.programID, i, maxLength, NULL, &size, &type, name);
                std::cout << name << std::endl;
                // Skip over any default opengl variables
                //if (name.find("gl_") != std::string::npos)
                //    continue;
            }
        }
    }

    void OpenGLApi::Cleanup() {
        // Clear shaders
        openGLShaders.clear();        

        // Clear gl context (windows will be cleared by window manager)
        for (OpenGLWindow window : openGLWindows) {
            SDL_GL_DeleteContext(window.gContext);
        }

        std::cout << "Opengl cleaned up" << std::endl;
    }
}  // namespace Crisp::Core