#include "CrispPCH.h"
#include "Camera.h"

namespace Crisp {
    Camera::Camera(Transform* transform) {
        transformComponent = transform;
    }

    Camera::~Camera() {}

    void Camera::RecreateCamera() {
        CRISP_PROFILE_FUNCTION();

        if (isOrthographic) {
            float aspect = width / height;

            float camWidth = 1.0f;
            float bottom = -camWidth;
            float top = camWidth;
            float left = bottom * aspect;
            float right = top * aspect;

            projectionMatrix = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
        } else {
            glm::perspective(fov, aspect, nearPlane, farPlane);
        }
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

    void Camera::SetPerspectiveCamera(const float _aspect, const float _fov, const float _nearPlane, const float _farPlane, const bool isMainCamera) {
        aspect = _aspect;
        fov = _fov;
        nearPlane = _nearPlane;
        farPlane = _farPlane;
        isOrthographic = false;

        RecreateCamera();
        if (isMainCamera)
            SetMainCamera(this);
    }

    void Camera::SetOrthographicCamera(const float _width, const float _height, const float _nearPlane, const float _farPlane, const bool isMainCamera) {
        width = _width;
        height = _height;
        nearPlane = _nearPlane;
        farPlane = _farPlane;
        isOrthographic = true;

        RecreateCamera();
        if (isMainCamera)
            SetMainCamera(this);
    }
}
