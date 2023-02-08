#include "CrispPCH.h"
#include "PerspectiveCamera.h"

namespace Crisp {
    PerspectiveCamera::PerspectiveCamera(Transform* transform, const float aspect, const float fov, const float nearPlane, const float farPlane, const bool isMainCamera) : transformComponent(transform), aspect(aspect), fov(fov), nearPlane(nearPlane), farPlane(farPlane) {
        // Create camera
        RecreateCamera();
        if (isMainCamera)
            SetMainCamera(this);
    }

    glm::mat4 PerspectiveCamera::GetProjectionMatrix() const {
        return projectionMatrix;
    }

    glm::mat4 PerspectiveCamera::GetViewMatrix() const {
        return glm::lookAt(transformComponent->GetPosition(), transformComponent->GetPosition() + transformComponent->Forward(), transformComponent->Up());
    }

    glm::mat4 PerspectiveCamera::GetViewProjectionMatrix() const {
        return projectionMatrix * GetViewMatrix();
    }

    void PerspectiveCamera::RecreateCamera() {
        projectionMatrix = glm::perspective(fov, aspect, nearPlane, farPlane);
    }
}
