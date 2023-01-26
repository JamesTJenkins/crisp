#pragma once
#include "Core.h"
#include "Window.h"

namespace Crisp {
	class CRISP_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> window;
		bool running = true;
	};

	// Defined in Crisp application
	Application* CreateApplication();
}
