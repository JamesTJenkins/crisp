#pragma once
#include "Crisp/Components/Camera.h"

namespace Crisp {
	class PerspectiveCamera : public Camera {
    public:
        PerspectiveCamera(Transform* transform, const float aspect, const float fov, const float nearPlane, const float farPlane, const bool isMainCamera);

        virtual void RecreateCamera() override;

        virtual glm::mat4 GetProjectionMatrix() const override;
        virtual glm::mat4 GetViewMatrix() const override;
        virtual glm::mat4 GetViewProjectionMatrix() const override;

        inline virtual Transform* GetTransform() const override { return transformComponent; }

        // Camera Settings
        float aspect;
        float fov;
        float nearPlane;
        float farPlane;
        // Camera Transform reference
        Transform* transformComponent;
    private:
        glm::mat4 projectionMatrix;
	};
}
