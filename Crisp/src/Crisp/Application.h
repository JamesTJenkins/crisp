#pragma once
#include "Core.h"

namespace Crisp {
	class CRISP_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// Defined in Crisp application
	Application* CreateApplication();
}
