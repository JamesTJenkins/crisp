#pragma once
#include "Crisp/Core/Layer.h"

namespace Crisp {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		ImGuiLayer(const ImGuiLayer& other) = delete;				// Copy construct
		ImGuiLayer& operator=(const ImGuiLayer& other) = delete;	// Copy assign

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate() override;
		virtual void OnEvent(const SDL_Event* e) override;

		void Begin();
		void End();
	};
}

