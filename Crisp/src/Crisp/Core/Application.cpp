#include "CrispPCH.h"
#include "Application.h"
#include <SDL.h>

#include "Crisp/Renderer/Renderer.h"
#include "Crisp/Core/Time.h"
#include "Crisp/Core/Input.h"

namespace Crisp {
	Application* Application::instance = nullptr; 

	Application::Application(const std::string& name) {
		CRISP_PROFILE_FUNCTION();

		CRISP_CORE_ASSERT(!instance, "Application already exists");
		instance = this;
		window = std::unique_ptr<Window>(Window::Create(WindowProperties(name)));

		Renderer::Initialize();

		imguiLayer = new ImGuiLayer();
		PushOverlay(imguiLayer);
	}

	Application::~Application() {
		CRISP_PROFILE_FUNCTION();

		Renderer::Shutdown();
		SDL_Quit();
	}

	void Application::Run() {
		CRISP_PROFILE_FUNCTION();

		Time time;

		while (running) {
			CRISP_PROFILE_SCOPE("Run loop");

			time.OnUpdate();

			SDL_Event e;
			while (SDL_PollEvent(&e)) {
				{
					CRISP_PROFILE_SCOPE("Window Polling");

					switch (e.type) {
					case SDL_WINDOWEVENT:
						switch (e.window.event) {
						case SDL_WINDOWEVENT_CLOSE:
							running = false;
							break;
						case SDL_WINDOWEVENT_RESIZED:
							Renderer::OnWindowResize(window->GetWidth(), window->GetHeight());
							break;
						}
						break;
					}
				}

				{
					CRISP_PROFILE_SCOPE("Layer::OnEvent");

					for (Layer* layer : layerStack)
						layer->OnEvent(&e);
				}
			}

			Input::OnUpdate();

			{
				CRISP_PROFILE_SCOPE("LayerStack OnUpdate");
				for (Layer* layer : layerStack)
					layer->OnUpdate();
			}

			{
				CRISP_PROFILE_SCOPE("LayerStack OnImGuiRender");

				imguiLayer->Begin();
				for (Layer* layer : layerStack)
					layer->OnImGuiRender();
				imguiLayer->End();
			}

			window->OnUpdate();
		}
	}

	void Application::Quit() {
		running = false;
	}

	void Application::PushLayer(Layer* layer) {
		CRISP_PROFILE_FUNCTION();

		layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		CRISP_PROFILE_FUNCTION();

		layerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::PopLayer(Layer* layer) {
		CRISP_PROFILE_FUNCTION();

		layer->OnDetach();
		layerStack.PopLayer(layer);
	}

	void Application::PopOverlay(Layer* overlay) {
		CRISP_PROFILE_FUNCTION();

		overlay->OnDetach();
		layerStack.PopLayer(overlay);
	}
}