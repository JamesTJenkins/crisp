#define SDL_MAIN_HANDLED
#include "Crisp.hpp"

#include "FeatureManager.hpp"
#include "SDL2.hpp"
#include "WindowManager.hpp"
#include "opengl/OpenGLApi.hpp"
// Testing
#include "ECS.hpp"
#include "components/Transform.hpp"
#include "components/Camera.hpp"
#include "components/MeshRenderer.hpp"

using namespace Crisp::Core;

int main() {
    std::cout << "Initializing Crisp..." << std::endl;

    // Load sdl2
    SDL2* sdl2 = FeatureManager::Get().AddFeature<SDL2>();
    // Load OpenGL
    OpenGLApi* openGLApi = FeatureManager::Get().AddFeature<OpenGLApi>();
    // Load window manager
    WindowManager* windowManager = FeatureManager::Get().AddFeature<WindowManager>();

    // Create window
    openGLApi->NewWindow("OpenGLTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400);
    ShaderImport testShader("assets/shaders/test.vert", "assets/shaders/test.frag");
    OpenGLShader& shader = openGLApi->AddShader(testShader);
    OpenGLMaterial& mat = openGLApi->AddMaterial(&openGLApi->openGLShaders[0]);
    ECS* ecs = FeatureManager::Get().AddFeature<ECS>();
    entt::entity e = ecs->registry.create();
    ecs->registry.emplace<Transform>(e, glm::vec3(0, 0, -10));
    ecs->registry.emplace<Camera>(e, e, (float)16/9);
    Mesh mesh = Primitive::CreateQuad();
    ecs->registry.emplace<MeshRenderer>(e, &mesh, &mat);

    bool running = true;
    while (running) {
        while (sdl2->PollEvent() != 0) {
            if (sdl2->HandleEvent() != 0)
                running = false;
        }

        openGLApi->Draw();
    }

    // Cleanup (automate in package manager eventually)
    windowManager->Cleanup();
    openGLApi->Cleanup();
    sdl2->Cleanup();

    return 0;
}