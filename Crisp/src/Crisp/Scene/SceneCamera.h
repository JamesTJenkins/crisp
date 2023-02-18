#pragma once
#include "Crisp/Components/Camera.h"

namespace Crisp {
	class SceneCamera : public Camera {
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void OnUpdate();
	private:
		Transform transform;
	};
}