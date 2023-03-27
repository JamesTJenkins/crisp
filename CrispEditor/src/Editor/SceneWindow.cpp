#include "SceneWindow.h"

#include <imgui/imgui.h>
#include <ImGuizmo.h>
#include <glm/gtc/type_ptr.hpp>

#include "Crisp/Math/Math.h"
#include "MousePicker.h"

namespace Crisp {
	SceneWindow::SceneWindow() {
		FrameBufferProperties props;
		props.attachment = { FrameBufferTextureFormat::RGBA8, FrameBufferTextureFormat::RINT, FrameBufferTextureFormat::DEPTH24STENCIL8 };
		props.width = 1280;
		props.height = 720;
		sceneViewFramebuffer = FrameBuffer::Create(props);
		sceneCam.SetOrthographicCamera(1280, 720, 10, -1, 1000, false);
	}

	void SceneWindow::SetContext(const Ref<Scene>& scene) {
		context = scene;
	}

	void SceneWindow::OnEditorUpdate() {
		if (sceneViewportFocused) {
			// Gizmo hotkeys
			if (Input::IsKeyPressed(CRISP_Q)) {
				gizmoType = -1;
			} else if (Input::IsKeyPressed(CRISP_W)) {
				gizmoType = ImGuizmo::OPERATION::TRANSLATE;
			} else if (Input::IsKeyPressed(CRISP_E)) {
				gizmoType = ImGuizmo::OPERATION::ROTATE;
			} else if (Input::IsKeyPressed(CRISP_R)) {
				gizmoType = ImGuizmo::OPERATION::SCALE;
			}

			if (Input::IsKeyPressed(CRISP_T)) {
				if (sceneCam.GetProjectionType() == Camera::Orthographic)
					sceneCam.SetProjectionType(Camera::Perspective);
				else
					sceneCam.SetProjectionType(Camera::Orthographic);
				sceneCam.RecreateCamera();
				CRISP_CORE_INFO("{0}", sceneCam.GetProjectionType());
			}

			sceneCam.OnUpdate();
		}
	}

	void SceneWindow::OnImGuiRender() {
		CRISP_PROFILE_FUNCTION();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Scene");
		auto viewportOffset = ImGui::GetCursorPos();
		sceneViewportFocused = ImGui::IsWindowFocused() && ImGui::IsWindowHovered();
		ImVec2 viewportSize = ImGui::GetContentRegionAvail();
		if (sceneViewportSize != *((glm::vec2*)&viewportSize)) {
			sceneViewFramebuffer->Resize(viewportSize.x, viewportSize.y);
			sceneCam.SetViewportSize(viewportSize.x, viewportSize.y);
			sceneViewportSize = { viewportSize.x, viewportSize.y };
		}
		ImGui::Image((void*)sceneViewFramebuffer->GetColorAttachmentRendererID(), viewportSize, ImVec2{0, 1}, ImVec2{1, 0});
		
		ImVec2 minBound = ImGui::GetWindowPos();
		minBound.x += viewportOffset.x;
		minBound.y += viewportOffset.y;

		ImVec2 maxBound = { minBound.x + viewportSize.x, minBound.y + viewportSize.y };
		viewportBounds[0] = { minBound.x, minBound.y };
		viewportBounds[1] = { maxBound.x, maxBound.y };

		// Gizmos
		Entity selected = GetSelectedEntity();
		if (selected && gizmoType != -1) {
			auto& component = selected.GetComponent<Transform>();
			if (sceneCam.GetProjectionType() == Camera::Orthographic)
				ImGuizmo::SetOrthographic(true);
			else
				ImGuizmo::SetOrthographic(false);

			ImGuizmo::SetDrawlist();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, (float)ImGui::GetWindowWidth(), (float)ImGui::GetWindowHeight());
			glm::mat4 transform = component.GetLocalToWorldMatrix();

			// Snapping
			bool snap = Input::IsKeyPressed(CRISP_LCTRL);
			float snapAmount = 0.5f;    // TRANSLATION SCALE
			if (gizmoType == ImGuizmo::OPERATION::ROTATE)
				snapAmount = 15.0f; // ROTATION
			float snapAmounts[3] = { snapAmount, snapAmount, snapAmount };

			ImGuizmo::Manipulate(glm::value_ptr(sceneCam.GetViewMatrix()),
				glm::value_ptr(sceneCam.GetProjectionMatrix()),
				(ImGuizmo::OPERATION)gizmoType,
				ImGuizmo::LOCAL,
				glm::value_ptr(transform),
				nullptr,
				snap ? snapAmounts : nullptr
			);

			if (ImGuizmo::IsUsing()) {
				glm::vec3 translation, rotation, scale;
				Math::DecomposeTransform(transform, translation, rotation, scale);
				glm::quat origRot = component.GetRotation();
				glm::quat deltaRotation = glm::quat(rotation) - origRot;

				component.SetPosition(translation);
				component.SetRotation(origRot + deltaRotation);
				component.SetScale(scale);
			}
		}
		ImGui::End();
		ImGui::PopStyleVar();
	}

	void SceneWindow::SceneWindowDraw() {
		// Scene camera
		sceneViewFramebuffer->Bind();
		RenderCommand::Clear();
		// Clear mouse picking attachment
		sceneViewFramebuffer->ClearAttachment(1, -1);

		Renderer::BeginScene(sceneCam);
		context->OnUpdateEditor();
		Renderer::EndScene();
		
		if (ImGui::IsMouseClicked(0) && sceneViewportFocused) {
			auto [mx, my] = ImGui::GetMousePos();
			mx -= viewportBounds[0].x;
			my -= viewportBounds[0].y;
			glm::vec2 viewportSize = viewportBounds[1] - viewportBounds[0];
			my = viewportSize.y - my;

			int mouseX = (int)mx;
			int mouseY = (int)my;

			if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y) {
				int pixelData = sceneViewFramebuffer->ReadPixel(1, mouseX, mouseY);
				SetSelectedEntity(pixelData == -1 ? Entity() : Entity{ (entt::entity)pixelData, context.get() });
			}
		}

		sceneViewFramebuffer->Unbind();
	}
}