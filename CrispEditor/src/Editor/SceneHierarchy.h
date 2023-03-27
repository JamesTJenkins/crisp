#pragma once
#include "Crisp.h"

namespace Crisp {
	class SceneHierarchy {
	public:
		SceneHierarchy() = default;
		SceneHierarchy(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
	private:
		Ref<Scene> context;
	};
}
