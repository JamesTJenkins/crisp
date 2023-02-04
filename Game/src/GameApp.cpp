#include <Crisp.h>

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <Platform/OpenGL/OpenGLShader.h>

class ExampleLayer : public Crisp::Layer {
public:
	ExampleLayer() : Layer("Example"), camTransform(glm::vec3(0, 0, -1)), cam(&camTransform, 16 / 9), col(1) {
		vertexArray.reset(Crisp::VertexArray::Create());

		float verts[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		Crisp::Ref<Crisp::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Crisp::VertexBuffer::Create(verts, sizeof(verts)));

		{
			Crisp::BufferLayout layout = {
				{ Crisp::ShaderDataType::Vec3, "Position" }
			};
			vertexBuffer->SetLayout(layout);
		}

		vertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int ind[3] = {
			0,1,2
		};

		Crisp::Ref<Crisp::IndexBuffer> indexBuffer;
		indexBuffer.reset(Crisp::IndexBuffer::Create(ind, sizeof(ind) / sizeof(uint32_t)));
		vertexArray->SetIndexBuffer(indexBuffer);

		std::string vert = R"(
			#version 330 core
			
			layout(location = 0) in vec3 position;

			uniform mat4 vp;
			uniform mat4 transform;
			uniform vec3 color;

			out vec3 pos;
			out vec3 col;

			void main() {
				pos = position;
				col = color;
				gl_Position = vp * transform * vec4(position, 1);
			}
		)";

		std::string frag = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 pos;
			in vec3 col;

			void main() {
				color = vec4(col, 1);
			}
		)";

		shader.reset(Crisp::Shader::Create(vert, frag));
	}

	void OnUpdate() override {
		// Camera movement
		glm::vec3 moveDir(0, 0, 0);
		if (Crisp::Input::IsKeyPressed(CRISP_LEFT))
			moveDir.x += 1;
		if (Crisp::Input::IsKeyPressed(CRISP_RIGHT))
			moveDir.x -= 1;
		if (Crisp::Input::IsKeyPressed(CRISP_UP))
			moveDir.z += 1;
		if (Crisp::Input::IsKeyPressed(CRISP_DOWN))
			moveDir.z -= 1;

		cam.transformComponent->SetPosition(cam.transformComponent->GetPosition() + (moveDir * (float)(Crisp::Time::deltaTime * 0.001)));

		// Rendering
		Crisp::RenderCommand::SetClearColor({ 1, 0, 1, 1 });
		Crisp::RenderCommand::Clear();

		Crisp::Renderer::BeginScene();
		shader->Bind();
		std::dynamic_pointer_cast<Crisp::OpenGLShader>(shader)->UploadUniformVec3("color", col);
		Crisp::Renderer::Submit(shader, vertexArray);
		Crisp::Renderer::EndScene();

		//Renderer::Flush();
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Color", glm::value_ptr(col));
		ImGui::End();
	}
private:
	Crisp::Ref<Crisp::Shader> shader;
	Crisp::Ref<Crisp::VertexArray> vertexArray;

	Crisp::Transform camTransform;
	Crisp::Camera cam;
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