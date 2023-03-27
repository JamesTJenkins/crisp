#pragma once
#include "Crisp.h"
#include "SceneHierarchy.h"

namespace Crisp {
	class SceneWindow {
	public:
		SceneWindow(SceneHierarchy* hierarchy);

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
		//glm::vec2 viewportSize = { 0.0f, 0.0f };
		glm::vec2 viewportBounds[2];

		int gizmoType = -1;

		// TODO: sort this out properly
		SceneHierarchy* hierarchy;
	};
}
