#pragma once
#include "Transform.h"

namespace Crisp {
    class Camera {
    public:
        virtual ~Camera() {}

        virtual void RecreateCamera() = 0;

        virtual glm::mat4 GetProjectionMatrix() const = 0;
        virtual glm::mat4 GetViewMatrix() const = 0;
        virtual glm::mat4 GetViewProjectionMatrix() const = 0;

        inline virtual Transform* GetTransform() const = 0;

        // Main camera reference (Gets the camera that is currently rendering to screen)
        inline static Camera* GetMainCamera() { return mainCamera; }
        inline static void SetMainCamera(Camera* value) { mainCamera = value; }

        static Camera* CreatePerspectiveCamera(Transform* transform, const float aspect, const float fov = 60, const float nearPlane = 0.1f, const float farPlane = 1000, const bool isMainCamera = true);
        static Camera* CreateOrthographicCamera(Transform* transform, const float width, const float height, const float nearPlane = 0.1f, const float farPlane = 1000, const bool isMainCamera = true);
    private:
        inline static Camera* mainCamera;
    };
}