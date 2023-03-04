#pragma once
#include "entt.hpp"

namespace Crisp {
	class Entity;
	class Scene {
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = "New Entity", const std::string& tag = "Default");
		void Destroy(Entity entity);

		void OnUpdate();
	private:
		entt::registry registry;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchy;
	};
}