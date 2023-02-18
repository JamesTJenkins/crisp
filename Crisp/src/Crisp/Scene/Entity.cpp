#include "CrispPCH.h"
#include "Entity.h"

namespace Crisp {
	Entity::Entity(entt::entity handle, Scene* scene) : entityHandle(handle), scene(scene) {}
}