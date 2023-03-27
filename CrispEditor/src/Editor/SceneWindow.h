#pragma once
#include "Crisp.h"

namespace Crisp {
	class SceneWindow {
	public:
		SceneWindow();

		void SetContext(const Ref<Scene>& scene);

		void OnEditorUpdate();
		void OnImGuiRender();
		void SceneWindowDraw();
	public:
		glm::vec2 sceneViewportSize = { 0, 0 };

		SceneCamera sceneCam;
	private:
		Ref<FrameBuffer> sceneViewFramebuffer;
		Ref<Scene> context;

		bool sceneViewportFocused = false;
		glm::vec2 viewportBounds[2];

		int gizmoType = -1;
	};
}
