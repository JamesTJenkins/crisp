#pragma once
#include <entt.hpp>

#include "Transform.hpp"

namespace Crisp::Core {
    class Camera {
    public:
        // Main camera reference (Gets the camera that is currently rendering to screen)
        static Camera* GetMainCamera();

        Camera(entt::entity& entity, const float aspect, const float fov = 60, const float nearPlane = 0.1f, const float farPlane = 1000.0f, const bool isOrthographic = false, const bool isMainCamera = true);

        // Camera Settings
        float aspect;
        float fov;
        float nearPlane;
        float farPlane;
        bool isOrthographic = false;
        // Camera Transform reference
        Transform* transformComponent;

        glm::mat4 GetViewMatrix() const;
        glm::mat4 WorldToCameraMatrix() const;
        glm::mat4 GetProjectionMatrix() const;

        void CreateCamera();
    private:
        static Camera* mainCamera;

        glm::mat4 projectionMatrix;
    };
}  // namespace Crisp::Core