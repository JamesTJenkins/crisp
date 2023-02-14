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
	ImGui::Begin("Statistics");
	ImGui::Text("Rendering Stats:");
	ImGui::Text("Draw Calls: %d", Crisp::Renderer::GetStats().DrawCalls);
	ImGui::Text("Quad Count: %d", Crisp::Renderer::GetStats().QuadCount);
	ImGui::Text("Vertex Count: %d", Crisp::Renderer::GetStats().GetTotalVertexCount());
	ImGui::Text("Index Count: %d", Crisp::Renderer::GetStats().GetTotalIndexCount());
	ImGui::End();
}

void Game2D::OnEvent(const SDL_Event* e) {

}
