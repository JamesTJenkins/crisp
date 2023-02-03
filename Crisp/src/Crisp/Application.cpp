#include "CrispPCH.h"
#include "Application.h"
#include <SDL.h>

#include "Crisp/Time.h"
#include "Crisp/Input.h"
#include "Crisp/Renderer/Renderer.h"

namespace Crisp {
	Application* Application::instance = nullptr; 

	Application::Application() : camTransform(glm::vec3(0, 0, -1)), cam(&camTransform, 16 / 9) {
		CRISP_CORE_ASSERT(!instance, "Application already exists")
			instance = this;
		window = std::unique_ptr<Window>(Window::Create());
		imguiLayer = new ImGuiLayer();
		PushOverlay(imguiLayer);

		// TESTING
		vertexArray.reset(VertexArray::Create());

		float verts[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(verts, sizeof(verts)));

		{
			BufferLayout layout = {
				{ ShaderDataType::Vec3, "Position" }
			};
			vertexBuffer->SetLayout(layout);
		}

		vertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int ind[3] = {
			0,1,2
		};

		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(ind, sizeof(ind) / sizeof(uint32_t)));
		vertexArray->SetIndexBuffer(indexBuffer);

		std::string vert = R"(
			#version 330 core
			
			layout(location = 0) in vec3 position;

			uniform mat4 vp;

			out vec3 pos;

			void main() {
				pos = position;
				gl_Position = vp * vec4(position, 1);
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

		shader.reset(new Shader(vert, frag));
		// TESTING
	}

	Application::~Application() {
		SDL_Quit();
	}

	void Application::Run() {
		Time time;

		while (running) {
			// Update time
			time.OnUpdate();

			RenderCommand::SetClearColor({ 1, 0, 1, 1 });
			RenderCommand::Clear();

			Renderer::BeginScene();
			// TESTING
			Renderer::Submit(shader, vertexArray);
			// TESTING
			Renderer::EndScene();

			//Renderer::Flush();

			// SDL Polling
			SDL_Event e;
			while (SDL_PollEvent(&e)) {
				// Handle window events
				switch (e.type) {
				case SDL_QUIT:
					running = false;
					break;
				}

				// Handle layer events
				for (Layer* layer : layerStack)
					layer->OnEvent(&e);
			}

			// Update input
			Input::OnUpdate();

			// Update layers
			for (Layer* layer : layerStack)
				layer->OnUpdate();

			imguiLayer->Begin();
			for (Layer* layer : layerStack)
				layer->OnImGuiRender();
			imguiLayer->End();

			// Update window
			window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer) {
		layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		layerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
}