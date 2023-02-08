#pragma once
#include "Crisp/Components/Camera.h"

namespace Crisp {
	class OrthographicCamera : public Camera {
    public:
        OrthographicCamera(Transform* transform, const float width, const float height, const float nearPlane, const float farPlane, const bool isMainCamera);

        virtual void RecreateCamera() override;

        virtual glm::mat4 GetProjectionMatrix() const override;
        virtual glm::mat4 GetViewMatrix() const override;
        virtual glm::mat4 GetViewProjectionMatrix() const override;

        inline virtual Transform* GetTransform() const override { return transformComponent; }

        // Camera Settings
        float width;
        float height;
        float nearPlane;
        float farPlane;
        // Camera Transform reference
        Transform* transformComponent;
    private:
        glm::mat4 projectionMatrix;
	};
}

