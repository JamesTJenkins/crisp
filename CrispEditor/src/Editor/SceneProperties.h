#pragma once
#include "Crisp/Scene/Entity.h"

namespace Crisp {
	class SceneProperties {
	public:
		SceneProperties();

		void OnImGuiRender();
	private:
		void DrawComponents(Entity entity);
	};
}
