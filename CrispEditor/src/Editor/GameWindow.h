#pragma once
#include "Crisp.h"

namespace Crisp {
	class GameWindow {
	public:
		GameWindow();

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();
		void GameWindowDraw();
	public:
		glm::vec2 gameViewportSize = { 0, 0 };
	private:
		Ref<FrameBuffer> gameViewFramebuffer;
		Ref<Scene> context;

		bool gameViewportFocused = false;
	};
}
