#include "SceneHierarchy.h"

#include <imgui/imgui.h>

#include "Crisp/Components/EntityProperties.h"

namespace Crisp {
	SceneHierarchy::SceneHierarchy(const Ref<Scene>& scene) {
		SetContext(scene);
	}

	void SceneHierarchy::SetContext(const Ref<Scene>& scene) {
		context = scene;
	}

	void SceneHierarchy::OnImGuiRender() {
		ImGui::Begin("Hierarchy");
		context->registry.each([&](auto entityID) {
			Entity entity{ entityID, context.get() };
			DrawEntityNode(entity);
		});
		ImGui::End();
	}

	void SceneHierarchy::DrawEntityNode(Entity entity) {
		auto& properties = entity.GetComponent<EntityProperties>();
		ImGuiTreeNodeFlags flags = ((selectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, properties.name.c_str());
		
		if (ImGui::IsItemClicked()) {
			selectionContext = entity;
		}

		if (opened) {
			ImGui::TreePop();
		}
	}
}