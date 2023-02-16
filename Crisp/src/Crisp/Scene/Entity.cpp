#include "CrispPCH.h"
#include "Entity.h"

namespace Crisp {
	Entity::Entity(entt::entity handle, Scene* scene, const std::string& name, const std::string& tag) : entityHandle(handle), scene(scene), name(name), tag(tag) {}
}