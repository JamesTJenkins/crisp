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

			if (ImGui::Button("Add Component"))
				ImGui::OpenPopup("AddComponent");

			if (ImGui::BeginPopup("AddComponent")) {
				if (ImGui::MenuItem("Camera")) {
					Camera cam = hierarchy->selectionContext.AddComponent<Camera>();
					cam.SetTransform(&hierarchy->selectionContext.GetComponent<Transform>());
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::MenuItem("Sprite Renderer")) {
					hierarchy->selectionContext.AddComponent<SpriteRenderer>();
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
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

		const ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap;

		if (entity.HasComponent<Transform>()) {
			if (ImGui::TreeNodeEx((void*)typeid(Transform).hash_code(), flags, "Transform")) {
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

		if (entity.HasComponent<Camera>()) {
			if (ImGui::TreeNodeEx((void*)typeid(Camera).hash_code(), flags, "Camera")) {
				auto& camera = entity.GetComponent<Camera>();

				const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
				const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.GetProjectionType()];
				if (ImGui::BeginCombo("Projection", currentProjectionTypeString)) {
					for (int i = 0; i < 2; i++) {
						bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
						if (ImGui::Selectable(projectionTypeStrings[i], isSelected)) {
							currentProjectionTypeString = projectionTypeStrings[i];
							camera.SetProjectionType((Camera::ProjectionType)i);
						}

						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}

				if (camera.GetProjectionType() == Camera::Perspective) {
					float fov = camera.GetPerspectiveFOV();
					if (ImGui::DragFloat("FOV", &fov))
						camera.SetPerspectiveFOV(fov);

					float nearPlane = camera.GetPerspectiveNearPlane();
					if (ImGui::DragFloat("Near Plane", &nearPlane))
						camera.SetPerspectiveNearPlane(nearPlane);

					float farPlane = camera.GetPerspectiveFarPlane();
					if (ImGui::DragFloat("Far Plane", &farPlane))
						camera.SetPerspectiveFarPlane(farPlane);
				} else {
					float size = camera.GetOrthographicSize();
					if (ImGui::DragFloat("Size", &size))
						camera.SetOrthographicSize(size);

					float nearPlane = camera.GetOrthographicNearPlane();
					if (ImGui::DragFloat("Near Plane", &nearPlane))
						camera.SetOrthographicNearPlane(nearPlane);

					float farPlane = camera.GetOrthographicFarPlane();
					if (ImGui::DragFloat("Far Plane", &farPlane))
						camera.SetOrthographicFarPlane(farPlane);
				}

				// TODO: Fix crashing when switching main camera
				bool isMainCam = camera == *camera.GetMainCamera();
				if (ImGui::Checkbox("Main Camera", &isMainCam)) {
					if (isMainCam) {
						camera.SetViewportSize(1280, 720);
						camera.SetMainCamera(&camera);
					}
				}

				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<SpriteRenderer>()) {
			bool open = ImGui::TreeNodeEx((void*)typeid(SpriteRenderer).hash_code(), flags, "Sprite Renderer");

			ImGui::SameLine(ImGui::GetWindowWidth() - 25);
			if (ImGui::Button("+", ImVec2{20, 20})) {
				ImGui::OpenPopup("ComponentSettings");
			}

			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings")) {
				if (ImGui::MenuItem("Remove Component"))
					removeComponent = true;
				ImGui::EndPopup();
			}

			if (open) {
				auto& sprite = entity.GetComponent<SpriteRenderer>();

				ImGui::ColorEdit4("Color", glm::value_ptr(sprite.color));
				
				ImGui::TreePop();
			}

			if (removeComponent)
				entity.RemoveComponent<SpriteRenderer>();
		}

		// TODO: Finish this
		if (entity.HasComponent<NativeScript>()) {
			if (ImGui::TreeNodeEx((void*)typeid(NativeScript).hash_code(), flags, "Script")) {
				auto& script = entity.GetComponent<NativeScript>();

				ImGui::TreePop();
			}
		}
	}
}