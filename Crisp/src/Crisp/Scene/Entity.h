#pragma once
#include "Scene.h"

namespace Crisp {
	class Entity {
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene, const std::string& name = "", const std::string& tag = "Default");
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

		std::string name;
		std::string tag;
	private:
		entt::entity entityHandle;
		Scene* scene = nullptr;
	};
}