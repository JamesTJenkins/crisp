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
        float hw = width / 2;
        float hh = height / 2;
        projectionMatrix = glm::ortho(-hw, hw, hh, -hh, nearPlane, farPlane);
    }
}