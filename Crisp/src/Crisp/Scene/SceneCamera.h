#pragma once
#include "Crisp/Components/Camera.h"

namespace Crisp {
	class SceneCamera : public Camera {
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void OnUpdate();
	private:
		void UpdateView();

		void Pan(const glm::vec2& delta);
		void Rotate(const glm::vec2& delta);
		void Zoom(const float delta);

		std::pair<float, float> PanSpeed() const;
		float RotationSpeed() const;
		float ZoomSpeed() const;
	private:
		Transform transform;
	private:
		glm::vec2 initialMousePosition;
		glm::vec3 focalPoint;
		float distance;
		float yaw, pitch;
	};
}