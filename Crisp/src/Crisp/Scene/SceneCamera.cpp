#include "CrispPCH.h"
#include "SceneCamera.h"

#include <Crisp.h>

namespace Crisp {
	SceneCamera::SceneCamera() {
		SetTransform(&transform);
	}

	void SceneCamera::OnUpdate() {
        glm::vec3 moveDir(0, 0, 0);
        if (Input::IsKeyPressed(CRISP_LEFT))
            moveDir.x += 1;
        if (Input::IsKeyPressed(CRISP_RIGHT))
            moveDir.x -= 1;
        if (Input::IsKeyPressed(CRISP_UP))
            moveDir.y += 1;
        if (Input::IsKeyPressed(CRISP_DOWN))
            moveDir.y -= 1;

        transform.SetPosition(transform.GetPosition() + moveDir * (float)(Time::deltaTime * 0.001));
	}
}