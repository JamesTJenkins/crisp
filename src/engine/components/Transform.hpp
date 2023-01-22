#pragma once
#include "../glm_common.hpp"

namespace Crisp::Core {
    class Transform {
       public:
        Transform(glm::vec3 position = glm::vec3(0, 0, 0), glm::quat rotation = glm::quat(), glm::vec3 scale = glm::vec3(1, 1, 1));
        Transform(glm::mat4 localToWorldMatrix);

        void Rotate(float angle_in_radians, glm::vec3 axis);
        void Rotate(glm::quat quaternion);

        static glm::quat EulerToQuat(glm::vec3 rotation_in_degrees);
        static glm::vec3 QuatToEuler(glm::quat quaternion);

        void SetPosition(glm::vec3 position);
        void SetRotation(glm::quat rotation);
        void SetScale(glm::vec3 scale);
        glm::vec3 GetPosition() const;
        glm::quat GetRotation() const;
        glm::vec3 GetScale() const;

        glm::vec3 Left() const;
        glm::vec3 Right() const;
        glm::vec3 Up() const;
        glm::vec3 Down() const;
        glm::vec3 Forward() const;
        glm::vec3 Backward() const;

        const glm::mat4& LocalToWorldMatrix();
        const glm::mat4& WorldToLocalMatrix();
       private:
        glm::vec3 position;
        glm::quat rotation;
        glm::vec3 scale;

        glm::mat4 localToWorldMatrix;
        glm::mat4 worldToLocalMatrix;
    };
}  // namespace Crisp::Core