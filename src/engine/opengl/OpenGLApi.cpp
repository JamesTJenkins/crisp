#include "OpenGLApi.hpp"

#include <gl/glu.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "../FeatureManager.hpp"
#include "../ECS.hpp"
#include "../WindowManager.hpp"
#include "../components/Camera.hpp"
#include "../components/MeshRenderer.hpp"

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

            std::cout << "Initialized openGL" << std::endl;
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
        renderer.Clear();
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

        // Get all mesh renderers
        ECS* ecs = FeatureManager::Get().GetFeature<ECS>();
        auto view = ecs->registry.view<Transform, MeshRenderer>();
        // Cycle through all mesh renderers
        for (auto entity : view) {
            // Get renderer and transform
            Transform& transform = view.get<Transform>(entity);
            MeshRenderer& meshRenderer = view.get<MeshRenderer>(entity);
            // Bind shader
            meshRenderer.material->shader->Bind();
            // MVP
            meshRenderer.material->shader->SetMat4("MVP", mainCamera->GetProjectionMatrix() * mainCamera->GetViewMatrix() * transform.GetLocalToWorldMatrix());
            // Draw
            OpenGLVertexArray va;
            //OpenGLIndexBuffer ib;
            //renderer.Draw(va, ib, *meshRenderer.material->shader);
        }
    }

    void OpenGLApi::Cleanup() {
        // Clear shaders
        openGLShaders.clear();        

        // Clear gl context (windows will be cleared by window manager)
        for (OpenGLWindow window : openGLWindows) {
            SDL_GL_DeleteContext(window.gContext);
        }

        std::cout << "OpenGL cleaned up" << std::endl;
    }
}  // namespace Crisp::Core