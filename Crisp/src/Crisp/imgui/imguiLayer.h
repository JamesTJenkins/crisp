#pragma once
#include "Crisp/Layer.h"

namespace Crisp {
	class CRISP_API imguiLayer : public Layer {
	public:
		imguiLayer();
		~imguiLayer();

		void OnAttach();
		void OnDetach();

		void OnUpdate();
		void OnEvent(const SDL_Event* e);
	private:

	};
}

