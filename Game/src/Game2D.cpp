#include "Game2D.h"
#include <imgui/imgui.h>

Game2D::Game2D() : Layer("Game2D"), camTransform(glm::vec3(0, 0, 0)), quadTransform(glm::vec3(0,0,-1), glm::quat(), glm::vec3(0.5f,0.5f,0.5f)), quad1Transform(glm::vec3(0, 0, -1)), cam(Crisp::Camera::CreateOrthographicCamera(&camTransform, 1280, 720, -1, 1)), color(0, 1, 1, 1) {
}

Game2D::~Game2D() {
}

void Game2D::OnAttach() {
	CRISP_PROFILE_FUNCTION();

	Crisp::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 0.1f });
	texture = Crisp::Texture2D::Create("assets/textures/bacon.png");
}

void Game2D::OnDetach() {
	CRISP_PROFILE_FUNCTION();
}

void Game2D::OnUpdate() {
	CRISP_PROFILE_FUNCTION();

	Crisp::Renderer::ResetStatistics();

	{
		CRISP_PROFILE_SCOPE("CameraController-Update");
		// Camera movement
		glm::vec3 moveDir(0, 0, 0);
		if (Crisp::Input::IsKeyPressed(CRISP_LEFT))
			moveDir.x += 1;
		if (Crisp::Input::IsKeyPressed(CRISP_RIGHT))
			moveDir.x -= 1;
		if (Crisp::Input::IsKeyPressed(CRISP_UP))
			moveDir.y += 1;
		if (Crisp::Input::IsKeyPressed(CRISP_DOWN))
			moveDir.y -= 1;

		cam->GetTransform()->SetPosition(cam->GetTransform()->GetPosition() + moveDir * (float)(Crisp::Time::deltaTime * 0.001));
	}
	{
		CRISP_PROFILE_SCOPE("Renderer Draw");
		// Rendering
		Crisp::RenderCommand::Clear();

		Crisp::Renderer::BeginScene();
		Crisp::Renderer::DrawQuad(quadTransform.GetLocalToWorldMatrix(), texture);
		Crisp::Renderer::DrawQuad(quad1Transform.GetLocalToWorldMatrix(), { 1,1,1,1 });

		//colorShader->Bind();
		//std::dynamic_pointer_cast<Crisp::OpenGLShader>(colorShader)->UploadUniformVec4("u_Color", color);
		//Crisp::Renderer::Submit(colorShader, vertexArray);

		Crisp::Renderer::EndScene();
	}
}

void Game2D::OnImGuiRender() {
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
                Crisp::Application::Get().Quit();
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

	ImGui::Begin("Statistics");
	ImGui::Text("Rendering Stats:");
	ImGui::Text("Draw Calls: %d", Crisp::Renderer::GetStats().DrawCalls);
	ImGui::Text("Quad Count: %d", Crisp::Renderer::GetStats().QuadCount);
	ImGui::Text("Vertex Count: %d", Crisp::Renderer::GetStats().GetTotalVertexCount());
	ImGui::Text("Index Count: %d", Crisp::Renderer::GetStats().GetTotalIndexCount());
	ImGui::End();

	ImGui::End();	// DOCKSPACE
}

void Game2D::OnEvent(const SDL_Event* e) {

}
