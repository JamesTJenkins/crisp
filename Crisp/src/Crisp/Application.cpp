#include "CrispPCH.h"
#include "Application.h"
#include "Crisp/Time.h"
#include <SDL.h>
#include <glad/glad.h>

namespace Crisp {
	Application* Application::instance = nullptr; 

	Application::Application() {
		CRISP_CORE_ASSERT(!instance, "Application already exists")
		instance = this;
		window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {
	}

	void Application::Run() {
		Time time;

		while (running) {
			// Update time
			time.OnUpdate();

			// Set pink for testing
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// SDL Polling
			SDL_Event e;
			while (SDL_PollEvent(&e)) {
				// Handle layer events
				for (Layer* layer : layerStack)
					layer->OnEvent(&e);

				// Handle window events
				switch (e.type) {
				case SDL_QUIT:
					running = false;
					break;
				}
			}

			// Update layers
			for (Layer* layer : layerStack)
				layer->OnUpdate();

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