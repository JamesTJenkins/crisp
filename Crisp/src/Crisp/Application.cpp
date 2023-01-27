#include "CrispPCH.h"
#include "Application.h"
#include <SDL.h>

namespace Crisp {
	Application::Application() {
		window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {
	}

	void Application::Run() {
		while (running) {
			// SDL
			SDL_Event e;
			while (SDL_PollEvent(&e)) {
				switch (e.type) {
				case SDL_QUIT:
					running = false;
					break;
				}
			}

			for (Layer* layer : layerStack)
				layer->OnUpdate();

			window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer) {
		layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay) {
		layerStack.PushOverlay(overlay);
	}
}