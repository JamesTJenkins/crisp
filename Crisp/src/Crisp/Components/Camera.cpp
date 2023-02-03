#include "CrispPCH.h"
#include "Camera.h"

namespace Crisp {
    Camera* Camera::mainCamera;

    Camera* Camera::GetMainCamera() {
        return mainCamera;
    }

    Camera::Camera(Transform* transform, const float aspect, const float fov, const float nearPlane, const float farPlane, const bool isOrthographic, const bool isMainCamera) : aspect(aspect), fov(fov), nearPlane(nearPlane), farPlane(farPlane), isOrthographic(isOrthographic) {
        // Try get Transform of entity from ecs, if none create new Transform
        transformComponent = transform;
        // Create camera
        CreateCamera();
        if(isMainCamera)
            mainCamera = this;
    }

    glm::mat4 Camera::GetProjectionMatrix() const {
        return projectionMatrix;
    }

    glm::mat4 Camera::GetViewMatrix() const {
        return glm::lookAt(transformComponent->GetPosition(), transformComponent->GetPosition() + transformComponent->Forward(), transformComponent->Up());
    }

    glm::mat4 Camera::GetViewProjectionMatrix() const {
        return projectionMatrix * GetViewMatrix();
    }

    // TODO: Fix camera to function with opengl rather than vulkan, hacky fix for now is -fov
    void Camera::CreateCamera() {
        if (!isOrthographic) {
            projectionMatrix = glm::perspective(-fov, aspect, nearPlane, farPlane);
        } else {
            projectionMatrix = glm::ortho(-fov, aspect, nearPlane, farPlane);
        }
    }
}