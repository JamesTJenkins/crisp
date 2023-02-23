#include "SceneProperties.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui_internal.h>

namespace Crisp {
	SceneProperties::SceneProperties(SceneHierarchy* hierarchy) : hierarchy(hierarchy) {}

	void SceneProperties::SetLinkedHierarchy(SceneHierarchy* _hierarchy) {
		hierarchy = _hierarchy;
	}

	// ------------------- STATIC FUNCTIONS -------------------------------

	static char buffer[256];

	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 80.0f) {
		ImGuiIO io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0,0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });

		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });

		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.7f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });

		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();
		ImGui::Columns(1);
		ImGui::PopID();
	}

	template<typename T, typename UIFunction>
	static void DrawComponent(const std::string& name, Entity entity, UIFunction function) {
		const ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

		if (entity.HasComponent<T>()) {
			auto& component = entity.GetComponent<T>();
			ImVec2 contextRegionAvailable = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), flags, name.c_str());
			ImGui::PopStyleVar();

			ImGui::SameLine(contextRegionAvailable.x - lineHeight * 0.5f);
			if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight })) {
				ImGui::OpenPopup("ComponentSettings");
			}

			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings")) {
				if (ImGui::MenuItem("Remove Component"))
					removeComponent = true;
				ImGui::EndPopup();
			}

			if (open) {
				function(component);
				ImGui::TreePop();
			}

			if (removeComponent)
				entity.RemoveComponent<T>();

			ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4{ 0,0,0,0 });
			ImGui::Separator();
			ImGui::PopStyleColor();
		}
	}

	// ------------------- END OF STATIC FUNCTIONS -------------------------------

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

		DrawComponent<Transform>("Transform", entity, [](auto& component) {
			glm::vec3 pos = component.GetPosition();
			DrawVec3Control("Position", pos);
			component.SetPosition(pos);

			glm::vec3 rotInDeg = Transform::QuatToEuler(component.GetRotation());
			DrawVec3Control("Rotation", rotInDeg);
			component.SetRotation(Transform::EulerToQuat(rotInDeg));

			glm::vec3 scale = component.GetScale();
			DrawVec3Control("Scale", scale);
			component.SetScale(scale);
		});

		DrawComponent<Camera>("Camera", entity, [](auto& component) {
			const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
			const char* currentProjectionTypeString = projectionTypeStrings[(int)component.GetProjectionType()];
			if (ImGui::BeginCombo("Projection", currentProjectionTypeString)) {
				for (int i = 0; i < 2; i++) {
					bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
					if (ImGui::Selectable(projectionTypeStrings[i], isSelected)) {
						currentProjectionTypeString = projectionTypeStrings[i];
						component.SetProjectionType((Camera::ProjectionType)i);
					}

					if (isSelected)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}

			if (component.GetProjectionType() == Camera::Perspective) {
				float fov = component.GetPerspectiveFOV();
				if (ImGui::DragFloat("FOV", &fov))
					component.SetPerspectiveFOV(fov);

				float nearPlane = component.GetPerspectiveNearPlane();
				if (ImGui::DragFloat("Near Plane", &nearPlane))
					component.SetPerspectiveNearPlane(nearPlane);

				float farPlane = component.GetPerspectiveFarPlane();
				if (ImGui::DragFloat("Far Plane", &farPlane))
					component.SetPerspectiveFarPlane(farPlane);
			} else {
				float size = component.GetOrthographicSize();
				if (ImGui::DragFloat("Size", &size))
					component.SetOrthographicSize(size);

				float nearPlane = component.GetOrthographicNearPlane();
				if (ImGui::DragFloat("Near Plane", &nearPlane))
					component.SetOrthographicNearPlane(nearPlane);

				float farPlane = component.GetOrthographicFarPlane();
				if (ImGui::DragFloat("Far Plane", &farPlane))
					component.SetOrthographicFarPlane(farPlane);
			}

			// TODO: Fix crashing when switching main camera
			bool isMainCam = component == *component.GetMainCamera();
			if (ImGui::Checkbox("Main Camera", &isMainCam)) {
				if (isMainCam) {
					component.SetViewportSize(1280, 720);
					component.SetMainCamera(&component);
				}
			}
		});

		DrawComponent<SpriteRenderer>("Sprite Renderer", entity, [](auto& component) {
			ImGui::ColorEdit4("Color", glm::value_ptr(component.color));
		});

		// TODO: Finish this
		//if (entity.HasComponent<NativeScript>()) {
		//	if (ImGui::TreeNodeEx((void*)typeid(NativeScript).hash_code(), flags, "Script")) {
		//		auto& script = entity.GetComponent<NativeScript>();
		//
		//		ImGui::TreePop();
		//	}
		//}

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
}