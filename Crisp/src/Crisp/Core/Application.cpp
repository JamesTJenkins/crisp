#include "CrispPCH.h"
#include "Application.h"
#include <SDL.h>

#include "Crisp/Core/Time.h"
#include "Crisp/Core/Input.h"

namespace Crisp {
	Application* Application::instance = nullptr; 

	Application::Application() {
		CRISP_CORE_ASSERT(!instance, "Application already exists")
			instance = this;
		window = std::unique_ptr<Window>(Window::Create());
		imguiLayer = new ImGuiLayer();
		PushOverlay(imguiLayer);
	}

	Application::~Application() {
		SDL_Quit();
	}

	void Application::Run() {
		Time time;

		while (running) {
			// Update time
			time.OnUpdate();

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

	void Application::PopLayer(Layer* layer) {
		layer->OnDetach();
		layerStack.PopLayer(layer);
	}

	void Application::PopOverlay(Layer* overlay) {
		overlay->OnDetach();
		layerStack.PopLayer(overlay);
	}
}