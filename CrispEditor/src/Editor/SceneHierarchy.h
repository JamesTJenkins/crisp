#pragma once
#include "Crisp.h"

namespace Crisp {
	class SceneHierarchy {
	public:
		SceneHierarchy() = default;
		SceneHierarchy(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();
	
		// TODO: Remove this once proper mouse picking implementation added
		Entity GetSelectedEntity() const { return selectionContext; }
	public:
		Entity selectionContext;
	private:
		void DrawEntityNode(Entity entity);
	private:
		Ref<Scene> context;
	};
}
