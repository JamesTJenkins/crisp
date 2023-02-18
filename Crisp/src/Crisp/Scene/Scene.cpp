#include "CrispPCH.h"
#include "Scene.h"

#include "Entity.h"
#include "Crisp/Renderer/Renderer.h"
#include "Crisp/Components/ScriptableObject.h"
#include "Crisp/Components/Transform.h"
#include "Crisp/Components/SpriteRenderer.h"

namespace Crisp {
	Scene::Scene() {}

	Scene::~Scene() {}

	Entity Scene::CreateEntity(const std::string& name) {
		Entity entity = { registry.create(), this, name };
		entity.AddComponent<Transform>();
		return entity;
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
		auto view = registry.view<Transform, SpriteRenderer>();
		for (auto [entity, transform, sprite] : view.each()) {
			Renderer::DrawQuad(transform.GetLocalToWorldMatrix(), sprite.color);
		}
	}
}