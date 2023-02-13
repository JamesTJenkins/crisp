#include "CrispPCH.h"
#include "OrthographicCamera.h"

namespace Crisp {
    OrthographicCamera::OrthographicCamera(Transform* transform, const float width, const float height, const float nearPlane, const float farPlane, const bool isMainCamera) : transformComponent(transform), width(width), height(height), nearPlane(nearPlane), farPlane(farPlane) {
        // Create camera
        RecreateCamera();
        if (isMainCamera)
            SetMainCamera(this);
    }

    glm::mat4 OrthographicCamera::GetProjectionMatrix() const {
        return projectionMatrix;
    }

    glm::mat4 OrthographicCamera::GetViewMatrix() const {
        return glm::lookAt(transformComponent->GetPosition(), transformComponent->GetPosition() + transformComponent->Forward(), transformComponent->Up());
    }

    glm::mat4 OrthographicCamera::GetViewProjectionMatrix() const {
        return projectionMatrix * GetViewMatrix();
    }

    void OrthographicCamera::RecreateCamera() {
        CRISP_PROFILE_FUNCTION();

        float aspect = width / height;

        float camWidth = 1.0f;
        float bottom = -camWidth;
        float top = camWidth;
        float left = bottom * aspect;
        float right = top * aspect;

        projectionMatrix = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
    }
}