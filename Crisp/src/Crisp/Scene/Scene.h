#pragma once
#include "entt.hpp"

namespace Crisp {
	class Entity;
	class Scene {
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = "New Entity", const std::string& tag = "Default");

		void OnUpdate();
	private:
		entt::registry registry;

		friend class Entity;
		friend class SceneHierarchy;
	};
}