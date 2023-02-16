#pragma once
#include "Transform.h"

namespace Crisp {
    class Camera {
    public:
        Camera() = default;
        Camera(Transform* transform);
        virtual ~Camera();

        void RecreateCamera();

        glm::mat4 GetProjectionMatrix() const;
        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetViewProjectionMatrix() const;

        inline void SetTransform(Transform* value) { transformComponent = value; }
        inline Transform* GetTransform() const { return transformComponent; }

        // Main camera reference (Gets the camera that is currently rendering to screen)
        inline static Camera* GetMainCamera() { return mainCamera; }
        inline static void SetMainCamera(Camera* value) { mainCamera = value; }

        void SetPerspectiveCamera(const float aspect, const float fov = 60, const float nearPlane = 0.1f, const float farPlane = 1000, const bool isMainCamera = true);
        void SetOrthographicCamera(const float width, const float height, const float nearPlane = 0.1f, const float farPlane = 1000, const bool isMainCamera = true);
    private:
        // General camera
        bool isOrthographic;
        glm::mat4 projectionMatrix;
        Transform* transformComponent;

        float nearPlane;
        float farPlane;
    private:
        // Orthographic
        float width;
        float height;
    private:
        // Perspective
        float aspect;
        float fov;
    private:
        // TODO: Move to scene
        inline static Camera* mainCamera;
    };
}