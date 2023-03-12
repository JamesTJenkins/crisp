#include "CrispPCH.h"
#include "SceneCamera.h"

#include <Crisp.h>

namespace Crisp {
	SceneCamera::SceneCamera() : focalPoint(glm::vec3(0,0,0)), distance(1.0f), pitch(0.0f), yaw(0.0f) {
        initialMousePosition = { Input::GetMouseX(), Input::GetMouseY() };
        
        SetTransform(&transform);
        UpdateView();
	}

	void SceneCamera::OnUpdate() {
        const glm::vec2& mouse{ Input::GetMouseX(), Input::GetMouseY() };
        glm::vec2 delta = (mouse - initialMousePosition) * 0.03f;
        initialMousePosition = mouse;
        int scrollDelta = Input::GetMouseScrollY();

        if (Input::IsMouseButtonHeld(CRISP_MOUSE_BUTTON_MIDDLE)) {
            Pan(delta);
        } else if (Input::IsMouseButtonHeld(CRISP_MOUSE_BUTTON_RIGHT)) {
            Rotate(delta);
        } else if (scrollDelta != 0) {
            Zoom((float)scrollDelta);
        }

        UpdateView();
    }

    void SceneCamera::UpdateView() {
        transform.SetPosition(focalPoint - transform.Forward() * (float)distance);
        transform.SetRotation(glm::quat(glm::vec3(pitch, -yaw, 0.0f)));
    }

    void SceneCamera::Pan(const glm::vec2& delta) {
        auto [xSpeed, ySpeed] = PanSpeed();
        focalPoint += -transform.Right() * delta.x * xSpeed * distance;
        focalPoint += transform.Up() * delta.y * ySpeed * distance;
    }

    void SceneCamera::Rotate(const glm::vec2& delta) {
        float yawSign = transform.Up().y < 0 ? -1.0f : 1.0f;
        yaw += yawSign * delta.x * RotationSpeed();
        pitch += delta.y * RotationSpeed();
    }

    void SceneCamera::Zoom(const float delta) {
        distance -= delta * ZoomSpeed();
        if (distance < 1.0f) {
            focalPoint += transform.Forward();
            distance = 1.0f;
        }
    }

    std::pair<float, float> SceneCamera::PanSpeed() const {
        return { 0.5f, 0.5f };
    }

    float SceneCamera::RotationSpeed() const {
        return 0.8f;
    }

    float SceneCamera::ZoomSpeed() const {
        return 1.0f;
    }
}