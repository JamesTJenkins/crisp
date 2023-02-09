#include "Game2D.h"
#include <imgui/imgui.h>
#include <Platform/OpenGL/OpenGLShader.h>

Game2D::Game2D() : Layer("Game2D"), camTransform(glm::vec3(0, 0, 0)), cam(Crisp::Camera::CreateOrthographicCamera(&camTransform, -(1280 / 720), 1280 / 720, -1, 1)), color(0, 1, 1, 1) {
}

Game2D::~Game2D() {
}

void Game2D::OnAttach() {
	Crisp::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 0.1f });

	vertexArray = Crisp::VertexArray::Create();

	float verts[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Crisp::Ref<Crisp::VertexBuffer> vertexBuffer;
	vertexBuffer = Crisp::VertexBuffer::Create(verts, sizeof(verts));

	Crisp::BufferLayout layout = {
		{ Crisp::ShaderDataType::Vec3, "Position" }
	};
	vertexBuffer->SetLayout(layout);
	vertexArray->AddVertexBuffer(vertexBuffer);

	unsigned int ind[6] = {
		0,1,2,
		2,3,0
	};

	Crisp::Ref<Crisp::IndexBuffer> indexBuffer;
	indexBuffer = Crisp::IndexBuffer::Create(ind, sizeof(ind) / sizeof(uint32_t));
	vertexArray->SetIndexBuffer(indexBuffer);

	colorShader = Crisp::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Game2D::OnDetach() {

}

void Game2D::OnUpdate() {
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

	cam->GetTransform()->SetPosition(cam->GetTransform()->GetPosition() + -(moveDir * (float)(Crisp::Time::deltaTime * 0.001)));

	// Rendering
	Crisp::RenderCommand::Clear();

	Crisp::Renderer::BeginScene();

	colorShader->Bind();
	std::dynamic_pointer_cast<Crisp::OpenGLShader>(colorShader)->UploadUniformVec4("u_Color", color);
	Crisp::Renderer::Submit(colorShader, vertexArray);

	Crisp::Renderer::EndScene();
}

void Game2D::OnImGuiRender() {

}

void Game2D::OnEvent(const SDL_Event* e) {

}
