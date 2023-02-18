#pragma once
#include "SceneHierarchy.h"

namespace Crisp {
	class SceneProperties {
	public:
		SceneProperties() = default;
		SceneProperties(SceneHierarchy* hierarchy);

		void SetLinkedHierarchy(SceneHierarchy* hierarchy);

		void OnImGuiRender();
	private:
		void DrawComponents(Entity entity);
	private:
		SceneHierarchy* hierarchy;
	};
}
