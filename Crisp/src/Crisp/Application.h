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

		inline static Application& Get() { return *instance; }

		inline Window& GetWindow() { return *window; }
	private:
		std::unique_ptr<Window> window;
		bool running = true;
		LayerStack layerStack;
	private:
		static Application* instance;
	};

	// Defined in Crisp application
	Application* CreateApplication();
}
