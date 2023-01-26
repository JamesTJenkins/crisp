#include "CrispPCH.h"
#include "Application.h"

#include "Crisp/Events/ApplicationEvent.h"

namespace Crisp {
	Application::Application() {
		window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {
	}

	void Application::Run() {
		while (running) {
			window->OnUpdate();
		}
	}
}