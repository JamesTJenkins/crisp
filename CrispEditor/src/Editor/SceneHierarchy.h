#pragma once
#include "Crisp/Core/Core.h"
#include "Crisp/Core/Log.h"
#include "Crisp/Scene/Scene.h"
#include "Crisp/Scene/Entity.h"

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
		Entity selectionContext;
	};
}
