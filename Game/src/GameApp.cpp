#include <Crisp.h>

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <Platform/OpenGL/OpenGLShader.h>

class ExampleLayer : public Crisp::Layer {
public:
	ExampleLayer() : Layer("Example"), camTransform(glm::vec3(0, 0, 0)), cam(Crisp::Camera::CreateOrthographicCamera(&camTransform, -(1280/720), 1280/720, -1, 1)), col(1) {
	//ExampleLayer() : Layer("Example"), camTransform(glm::vec3(0, 0, -1)), cam(Crisp::Camera::CreatePerspectiveCamera(&camTransform, 1280/720)), col(1) {
		Crisp::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 0.1f });

		vertexArray.reset(Crisp::VertexArray::Create());

		float verts[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Crisp::Ref<Crisp::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Crisp::VertexBuffer::Create(verts, sizeof(verts)));

		Crisp::BufferLayout layout = {
			{ Crisp::ShaderDataType::Vec3, "Position" },
			{ Crisp::ShaderDataType::Vec2, "Texcoord" }
		};
		vertexBuffer->SetLayout(layout);
		vertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int ind[6] = {
			0,1,2,
			2,3,0
		};

		Crisp::Ref<Crisp::IndexBuffer> indexBuffer;
		indexBuffer.reset(Crisp::IndexBuffer::Create(ind, sizeof(ind) / sizeof(uint32_t)));
		vertexArray->SetIndexBuffer(indexBuffer);

		auto texShader = lib.Load("textureShader", "assets/shaders/texture.glsl");

		texture = Crisp::Texture2D::Create("assets/textures/bacon.png");
		sampler = Crisp::Sampler::Create();

		std::dynamic_pointer_cast<Crisp::OpenGLShader>(texShader)->Bind();
		std::dynamic_pointer_cast<Crisp::OpenGLShader>(texShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate() override {
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
		auto texShader = lib.Get("textureShader");
		texShader->Bind();
		sampler->Bind();
		texture->Bind();
		Crisp::Renderer::Submit(texShader, vertexArray);
		Crisp::Renderer::EndScene();

		//Renderer::Flush();
	}

	virtual void OnImGuiRender() override {
		//ImGui::Begin("Settings");
		//ImGui::ColorEdit3("Color", glm::value_ptr(col));
		//ImGui::End();
	}
private:
	Crisp::ShaderLibrary lib;
	Crisp::Ref<Crisp::VertexArray> vertexArray;

	Crisp::Ref<Crisp::Sampler> sampler;
	Crisp::Ref<Crisp::Texture2D> texture;

	Crisp::Transform camTransform;
	Crisp::Camera* cam;
	glm::vec3 col;
};

class Game : public Crisp::Application {
public:
	Game() {
		PushLayer(new ExampleLayer());
	}
	~Game() {}
};

Crisp::Application* Crisp::CreateApplication() {
	return new Game();
}