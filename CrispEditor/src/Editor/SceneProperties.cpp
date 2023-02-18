#include "SceneProperties.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Crisp {
	static char buffer[256];

	SceneProperties::SceneProperties(SceneHierarchy* hierarchy) : hierarchy(hierarchy) {}

	void SceneProperties::SetLinkedHierarchy(SceneHierarchy* _hierarchy) {
		hierarchy = _hierarchy;
	}

	void SceneProperties::OnImGuiRender() {
		ImGui::Begin("Properties");
		if (hierarchy->selectionContext) {
			DrawComponents(hierarchy->selectionContext);
		}
		ImGui::End();
	}

	void SceneProperties::DrawComponents(Entity entity) {
		if (entity.HasComponent<EntityProperties>()) {
			auto& properties = entity.GetComponent<EntityProperties>();

			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), properties.name.c_str());
			if (ImGui::InputText("Name", buffer, sizeof(buffer))) {
				properties.name = std::string(buffer);
			}

			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), properties.tag.c_str());
			if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {
				properties.tag = std::string(buffer);
			}
		}

		if (entity.HasComponent<Transform>()) {
			if (ImGui::TreeNodeEx((void*)typeid(Transform).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform")) {
				auto& transform = entity.GetComponent<Transform>();

				glm::vec3 pos = transform.GetPosition();
				if (ImGui::DragFloat3("Position", glm::value_ptr(pos), 0.1f)) {
					transform.SetPosition(pos);
				}

				glm::vec3 rotInDeg = Transform::QuatToEuler(transform.GetRotation());
				if (ImGui::DragFloat3("Rotation", glm::value_ptr(rotInDeg), 0.1f)) {
					transform.SetRotation(Transform::EulerToQuat(rotInDeg));
				}

				glm::vec3 scale = transform.GetScale();
				if (ImGui::DragFloat3("Scale", glm::value_ptr(scale), 0.1f)) {
					transform.SetScale(scale);
				}

				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<SpriteRenderer>()) {
			if (ImGui::TreeNodeEx((void*)typeid(SpriteRenderer).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Sprite Renderer")) {
				auto& sprite = entity.GetComponent<SpriteRenderer>();

				ImGui::ColorEdit4("Color", glm::value_ptr(sprite.color));
				
				ImGui::TreePop();
			}
		}

		// TODO: Finish this
		if (entity.HasComponent<NativeScript>()) {
			if (ImGui::TreeNodeEx((void*)typeid(NativeScript).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Script")) {
				auto& script = entity.GetComponent<NativeScript>();

				ImGui::TreePop();
			}
		}
	}
}