#include "CrispPCH.h"
#include "Application.h"

#include "Crisp/Events/ApplicationEvent.h"
#include "Log.h"

namespace Crisp {
	Application::Application() {
	}

	Application::~Application() {
	}

	void Application::Run() {
		// EVENT TEST
		WindowResizeEvent e(1280, 720);
		CRISP_TRACE(e);
		// EVENT TEST

		while (true) {}
	}
}