#include "Camera.hpp"
#include "../FeatureManager.hpp"
#include "../ECS.hpp"

namespace Crisp::Core {
    Camera* Camera::mainCamera;

    Camera* Camera::GetMainCamera() {
        return mainCamera;
    }

    Camera::Camera(entt::entity& entity, const float aspect, const float fov, const float nearPlane, const float farPlane, const bool isOrthographic, const bool isMainCamera) : aspect(aspect), fov(fov), nearPlane(nearPlane), farPlane(farPlane), isOrthographic(isOrthographic) {
        // Try get Transform of entity from ecs, if none create new Transform
        ECS* ecs = FeatureManager::Get().GetFeature<ECS>();
        transformComponent = ecs->registry.try_get<Transform>(entity);
        if (transformComponent == nullptr)
            transformComponent = &ecs->registry.emplace<Transform>(entity);
        // Create camera
        CreateCamera();
        if(isMainCamera)
            mainCamera = this;
    }

    glm::mat4 Camera::GetViewMatrix() const {
        return glm::lookAt(transformComponent->GetPosition(), transformComponent->GetPosition() + transformComponent->Forward(), transformComponent->Up());
    }

    glm::mat4 Camera::WorldToCameraMatrix() const {
        return projectionMatrix * glm::lookAt(transformComponent->GetPosition(), transformComponent->GetPosition() + transformComponent->Forward(), transformComponent->Up());
    }

    glm::mat4 Camera::GetProjectionMatrix() const {
        return projectionMatrix;
    }

    void Camera::CreateCamera() {
        if (!isOrthographic) {
            projectionMatrix = glm::perspective(fov, aspect, nearPlane, farPlane);
        } else {
            projectionMatrix = glm::ortho(fov, aspect, nearPlane, farPlane);
        }
    }
}  // namespace Crisp::Core