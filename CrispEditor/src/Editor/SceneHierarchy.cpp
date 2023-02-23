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

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			selectionContext = {};

		if (ImGui::BeginPopupContextWindow(0, 1)) {
			if (ImGui::MenuItem("Create Empty"))
				context->CreateEntity("Empty");

			ImGui::EndPopup();
		}

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

		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem()) {
			if (ImGui::MenuItem("Delete Entity"))
				entityDeleted = true;
			ImGui::EndPopup();
		}

		if (opened) {
			ImGui::TreePop();
		}

		// Delay entity deletion to the end
		if (entityDeleted) {
			if (selectionContext == entity)
				selectionContext = {};
			context->Destroy(entity);
		}
	}
}