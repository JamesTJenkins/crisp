#include <Crisp.h>

#include <imgui/imgui.h>

class ExampleLayer : public Crisp::Layer {
public:
	ExampleLayer() : Layer("Example"), camTransform(glm::vec3(0, 0, -1)), cam(&camTransform, 16 / 9) {
		vertexArray.reset(Crisp::VertexArray::Create());

		float verts[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		std::shared_ptr<Crisp::VertexBuffer> vertexBuffer;
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

		std::shared_ptr<Crisp::IndexBuffer> indexBuffer;
		indexBuffer.reset(Crisp::IndexBuffer::Create(ind, sizeof(ind) / sizeof(uint32_t)));
		vertexArray->SetIndexBuffer(indexBuffer);

		std::string vert = R"(
			#version 330 core
			
			layout(location = 0) in vec3 position;

			uniform mat4 vp;
			uniform mat4 transform;

			out vec3 pos;

			void main() {
				pos = position;
				gl_Position = vp * transform * vec4(position, 1);
			}
		)";

		std::string frag = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 pos;

			vec3 hsv2rgb (vec3 c) {
				vec4 k = vec4 (1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
				vec3 p = abs (fract (c.xxx + k.xyz) * 6.0 - k.www);
				return c.z * mix (k.xxx, clamp (p - k.xxx, 0.0, 1.0), c.y);
			}

			void main() {
				color = vec4(hsv2rgb (vec3 (sin (pos.x), 1, 1)), 1);
			}
		)";

		shader.reset(new Crisp::Shader(vert, frag));
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
		Crisp::Renderer::Submit(shader, vertexArray);
		Crisp::Renderer::EndScene();

		//Renderer::Flush();
	}

	virtual void OnImGuiRender() override {
		
	}
private:
	std::shared_ptr<Crisp::Shader> shader;
	std::shared_ptr<Crisp::VertexArray> vertexArray;
	Crisp::Transform camTransform;
	Crisp::Camera cam;
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