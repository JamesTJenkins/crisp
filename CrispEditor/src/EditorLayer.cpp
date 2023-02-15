#include "EditorLayer.h"
#include <imgui/imgui.h>

namespace Crisp {
    EditorLayer::EditorLayer() : Layer("EditorLayer"), camTransform(glm::vec3(0, 0, 0)), quadTransform(glm::vec3(0, 0, -1), glm::quat(), glm::vec3(0.5f, 0.5f, 0.5f)), quad1Transform(glm::vec3(0, 0, -1)), cam(Camera::CreateOrthographicCamera(&camTransform, 1280, 720, -1, 1)), color(0, 1, 1, 1) {}

    EditorLayer::~EditorLayer() {}

    void EditorLayer::OnAttach() {
        CRISP_PROFILE_FUNCTION();

        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 0.1f });
        texture = Texture2D::Create("assets/textures/bacon.png");

        FrameBufferProperties props;
        props.width = 1280;
        props.height = 720;
        framebuffer = FrameBuffer::Create(props);
    }

    void EditorLayer::OnDetach() {
        CRISP_PROFILE_FUNCTION();
    }

    void EditorLayer::OnUpdate() {
        CRISP_PROFILE_FUNCTION();

        Renderer::ResetStatistics();

        {
            CRISP_PROFILE_SCOPE("CameraController-Update");
            // Camera movement
            glm::vec3 moveDir(0, 0, 0);
            if (Input::IsKeyPressed(CRISP_LEFT))
                moveDir.x += 1;
            if (Input::IsKeyPressed(CRISP_RIGHT))
                moveDir.x -= 1;
            if (Input::IsKeyPressed(CRISP_UP))
                moveDir.y += 1;
            if (Input::IsKeyPressed(CRISP_DOWN))
                moveDir.y -= 1;

            // Only allow movement if the viewport is focused
            if (viewportFocused)
                cam->GetTransform()->SetPosition(cam->GetTransform()->GetPosition() + moveDir * (float)(Time::deltaTime * 0.001));
        }
        {
            CRISP_PROFILE_SCOPE("Renderer Draw");
            framebuffer->Bind();
            RenderCommand::Clear();

            Renderer::BeginScene();
            Renderer::DrawQuad(quadTransform.GetLocalToWorldMatrix(), texture);
            Renderer::DrawQuad(quad1Transform.GetLocalToWorldMatrix(), { 1,1,1,1 });

            //colorShader->Bind();
            //std::dynamic_pointer_cast<OpenGLShader>(colorShader)->UploadUniformVec4("u_Color", color);
            //Renderer::Submit(colorShader, vertexArray);

            Renderer::EndScene();
            framebuffer->Unbind();
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
        viewportFocused = ImGui::IsWindowFocused();
        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        if (sceneViewportSize != *((glm::vec2*)&viewportSize)) {
            framebuffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
            sceneViewportSize = { viewportSize.x, viewportSize.y };
        }
        ImGui::Image((void*)framebuffer->GetColorAttachmentRendererID(), viewportSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::Begin("Statistics");
        ImGui::Text("Rendering Stats:");
        ImGui::Text("Draw Calls: %d", Renderer::GetStats().DrawCalls);
        ImGui::Text("Quad Count: %d", Renderer::GetStats().QuadCount);
        ImGui::Text("Vertex Count: %d", Renderer::GetStats().GetTotalVertexCount());
        ImGui::Text("Index Count: %d", Renderer::GetStats().GetTotalIndexCount());
        ImGui::End();

        ImGui::End();	// DOCKSPACE
    }

    void EditorLayer::OnEvent(const SDL_Event* e) {

    }
}
