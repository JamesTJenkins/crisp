#include "EditorLayer.h"
#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

// TEST
#include "Test.h"
// TEST

namespace Crisp {
    EditorLayer::EditorLayer() : Layer("EditorLayer") {}

    EditorLayer::~EditorLayer() {}

    void EditorLayer::OnAttach() {
        CRISP_PROFILE_FUNCTION();

        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 0.1f });
        texture = Texture2D::Create("assets/textures/bacon.png");

        FrameBufferProperties props;
        props.width = 1280;
        props.height = 720;
        gameViewFramebuffer = FrameBuffer::Create(props);
        sceneViewFramebuffer = FrameBuffer::Create(props);

        activeScene = CreateRef<Scene>();
        camEntity = activeScene->CreateEntity("New Cam");
        camEntity.AddComponent<Camera>(&camEntity.GetComponent<Transform>()).SetOrthographicCamera(1280, 720);
        quadEntity = activeScene->CreateEntity("New Quad");
        quadEntity.AddComponent<SpriteRenderer>();

        sceneCam.SetOrthographicCamera(1280, 720, 0.1f, 1000.0f, false);

        // TEST
        activeScene->CreateEntity("Test").AddComponent<NativeScript>().Bind<Test>();
        // TEST
    }

    void EditorLayer::OnDetach() {
        CRISP_PROFILE_FUNCTION();
    }

    void EditorLayer::OnUpdate() {
        CRISP_PROFILE_FUNCTION();

        // Only allow movement if the viewport is focused
        if (sceneViewportFocused)
            sceneCam.OnUpdate();

        {
            CRISP_PROFILE_SCOPE("Scene Renderer Draw");

            // Scene camera
            sceneViewFramebuffer->Bind();
            RenderCommand::Clear();
            Renderer::BeginScene(sceneCam);
            activeScene->OnUpdate();
            Renderer::EndScene();
            sceneViewFramebuffer->Unbind();
        }

        // This needs to be after scene render loop otherwise it will give
        // stats for rendering both scene and game view
        Renderer::ResetStatistics();

        {
            CRISP_PROFILE_SCOPE("Renderer Draw");

            // Game view camera
            gameViewFramebuffer->Bind();
            RenderCommand::Clear();
            Renderer::BeginScene(*(Camera::GetMainCamera()));
            activeScene->OnUpdate();
            Renderer::EndScene();
            gameViewFramebuffer->Unbind();
        }
    }

    void EditorLayer::OnImGuiRender() {
        static bool dockspaceOpen = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen) {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        } else {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Crisp Dockspace", &dockspaceOpen, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("Dockspace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit"))
                    Application::Get().Quit();
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Scene");
        sceneViewportFocused = ImGui::IsWindowFocused();
        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        if (sceneViewportSize != *((glm::vec2*)&viewportSize)) {
            sceneViewFramebuffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
            sceneViewportSize = { viewportSize.x, viewportSize.y };
        }
        ImGui::Image((void*)sceneViewFramebuffer->GetColorAttachmentRendererID(), viewportSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Game");
        gameViewportFocused = ImGui::IsWindowFocused();
        viewportSize = ImGui::GetContentRegionAvail();
        if (gameViewportSize != *((glm::vec2*)&viewportSize)) {
            gameViewFramebuffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
            gameViewportSize = { viewportSize.x, viewportSize.y };
        }
        ImGui::Image((void*)gameViewFramebuffer->GetColorAttachmentRendererID(), viewportSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::Begin("Statistics");
        ImGui::Text("Rendering Stats:");
        ImGui::Text("Draw Calls: %d", Renderer::GetStats().DrawCalls);
        ImGui::Text("Quad Count: %d", Renderer::GetStats().QuadCount);
        ImGui::Text("Vertex Count: %d", Renderer::GetStats().GetTotalVertexCount());
        ImGui::Text("Index Count: %d", Renderer::GetStats().GetTotalIndexCount());

        ImGui::Separator();
        ImGui::Text("%s", quadEntity.name.c_str());
        auto& color = quadEntity.GetComponent<SpriteRenderer>().color;
        ImGui::ColorEdit4("Color: ", glm::value_ptr(color));
        ImGui::Separator();

        ImGui::End();

        ImGui::End();	// DOCKSPACE
    }

    void EditorLayer::OnEvent(const SDL_Event* e) {

    }
}
