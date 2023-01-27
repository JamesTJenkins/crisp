#pragma once
#include "Core.h"
#include "Window.h"
#include "LayerStack.h"

namespace Crisp {
	class CRISP_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		std::unique_ptr<Window> window;
		bool running = true;
		LayerStack layerStack;
	};

	// Defined in Crisp application
	Application* CreateApplication();
}
