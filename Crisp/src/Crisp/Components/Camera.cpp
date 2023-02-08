#include "CrispPCH.h"
#include "Camera.h"

#include "Crisp/Components/PerspectiveCamera.h"
#include "Crisp/Components/OrthographicCamera.h"

namespace Crisp {
    Camera* Camera::CreatePerspectiveCamera(Transform* transform, const float aspect, const float fov, const float nearPlane, const float farPlane, const bool isMainCamera) {
        return new PerspectiveCamera(transform, aspect, fov, nearPlane, farPlane, isMainCamera);
    }

    Camera* Camera::CreateOrthographicCamera(Transform* transform, const float width, const float height, const float nearPlane, const float farPlane, const bool isMainCamera) {
        return new OrthographicCamera(transform, width, height, nearPlane, farPlane, isMainCamera);
    }
}
