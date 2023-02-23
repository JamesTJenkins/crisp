#pragma once
#include "Scene.h"

namespace Crisp {
	class Entity {
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) { 
			CRISP_CORE_ASSERT(!HasComponent<T>(), "Entity already has this component.");
			return scene->registry.emplace<T>(entityHandle, std::forward<Args>(args)...); 
		}

		template<typename T>
		void RemoveComponent() {
			CRISP_CORE_ASSERT(HasComponent<T>(), "Entity doesnt have this component.");
			scene->registry.remove<T>(entityHandle);
		}

		template<typename T>
		T& GetComponent() { 
			CRISP_CORE_ASSERT(HasComponent<T>(), "Entity doesnt have this component.");
			return scene->registry.get<T>(entityHandle); 
		}

		template<typename T>
		bool HasComponent() { 
			return scene->registry.any_of<T>(entityHandle); 
		}

		operator bool() const { return entityHandle != entt::null; }
		operator uint32_t() const { return (uint32_t)entityHandle; }	// entt::entity identifier is a uint32_t this just makes life easier
		operator entt::entity() const { return entityHandle; }

		bool operator==(const Entity& other) const { return entityHandle == other.entityHandle && scene == other.scene; }
		bool operator!=(const Entity& other) const { return !(*this == other); }
	private:
		entt::entity entityHandle = entt::null;
		Scene* scene = nullptr;
	};
}