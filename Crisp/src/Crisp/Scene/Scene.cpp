#include "CrispPCH.h"
#include "Scene.h"

#include "Entity.h"
#include "Crisp/Renderer/Renderer.h"
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
		auto view = registry.view<Transform, SpriteRenderer>();
		for (auto [entity, transform, sprite] : view.each()) {
			Renderer::DrawQuad(transform.GetLocalToWorldMatrix(), sprite.color);
		}
	}
}