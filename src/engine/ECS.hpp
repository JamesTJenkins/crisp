#pragma once
#include <entt.hpp>

namespace Crisp::Core {
    class ECS {
       public:
        ECS() {};
        ~ECS() {};

        entt::registry registry;
    };
}  // namespace Crisp::Core