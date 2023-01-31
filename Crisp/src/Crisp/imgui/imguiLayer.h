#pragma once
#include "Crisp/Layer.h"

namespace Crisp {
	class CRISP_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(const SDL_Event* e) override;

		void Begin();
		void End();
	};
}

