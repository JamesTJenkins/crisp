#pragma once
#include "Transform.h"

namespace Crisp {
    class Camera {
    public:
        // Main camera reference (Gets the camera that is currently rendering to screen)
        static Camera* GetMainCamera();

        Camera(Transform* transform, const float aspect, const float fov = 60, const float nearPlane = 0.1f, const float farPlane = 1000.0f, const bool isOrthographic = false, const bool isMainCamera = true);

        // Camera Settings
        float aspect;
        float fov;
        float nearPlane;
        float farPlane;
        bool isOrthographic = false;
        // Camera Transform reference
        Transform* transformComponent;

        glm::mat4 GetProjectionMatrix() const;
        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetViewProjectionMatrix() const;

        void CreateCamera();
    private:
        static Camera* mainCamera;

        glm::mat4 projectionMatrix;
    };
}