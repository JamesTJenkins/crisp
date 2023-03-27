#include "CrispPCH.h"
#include "Scene.h"

#include "Crisp/Renderer/Renderer.h"

#include "Entity.h"
#include "Crisp/Components/EntityProperties.h"
#include "Crisp/Components/ScriptableObject.h"
#include "Crisp/Components/Transform.h"
#include "Crisp/Components/SpriteRenderer.h"

namespace Crisp {
	Scene::Scene() {}

	Scene::~Scene() {}

	Entity Scene::CreateEntity(const std::string& name, const std::string& tag) {
		Entity entity = { registry.create(), this };
		entity.AddComponent<EntityProperties>(name, tag);
		entity.AddComponent<Transform>();
		return entity;
	}

	void Scene::Destroy(Entity entity) {
		registry.destroy(entity);
	}

	void Scene::OnUpdate() {
		// SCRIPT ONUPDATE
		// TODO: Make this only happen when playing the game
		// TODO: Implement OnDestroy after implementing game stop button
		registry.view<NativeScript>().each([=](auto entity, auto& nativeScript) {
			if (!nativeScript.Instance) {
				nativeScript.Instance = nativeScript.InstantiateScript();
				nativeScript.Instance->entity = Entity{ entity, this };
				nativeScript.Instance->OnCreate();
			}

			nativeScript.Instance->OnUpdate();
		});

		// RENDER
		registry.view<Transform, SpriteRenderer>().each([=](auto entity, Transform& transform, SpriteRenderer& sprite) {
			Renderer::DrawSprite(transform.GetLocalToWorldMatrix(), sprite, (int)entity);
		});
	}

	void Scene::OnUpdateEditor() {
		// RENDER
		registry.view<Transform, SpriteRenderer>().each([=](auto entity, Transform& transform, SpriteRenderer& sprite) {
			Renderer::DrawSprite(transform.GetLocalToWorldMatrix(), sprite, (int)entity);
		});
	}
}