#include "GameWindow.h"
#include <imgui/imgui.h>

namespace Crisp {
	GameWindow::GameWindow() {
		FrameBufferProperties props;
		props.width = 1280;
		props.height = 720;
		gameViewFramebuffer = FrameBuffer::Create(props);
	}

	void GameWindow::SetContext(const Ref<Scene>& scene) {
		context = scene;
	}

	void GameWindow::OnImGuiRender() {
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Game");
		gameViewportFocused = ImGui::IsWindowFocused() && ImGui::IsWindowHovered();
		ImVec2 viewportSize = ImGui::GetContentRegionAvail();
		if (Camera::GetMainCamera() != nullptr) {
			if (gameViewportSize != *((glm::vec2*)&viewportSize)) {
				Camera::GetMainCamera()->SetViewportSize(viewportSize.x, viewportSize.y);
				gameViewportSize = { viewportSize.x, viewportSize.y };
			}
		}
		ImGui::Image((void*)gameViewFramebuffer->GetColorAttachmentRendererID(), viewportSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		ImGui::End();
		ImGui::PopStyleVar();
	}

	void GameWindow::GameWindowDraw() {
		// Game view camera
		gameViewFramebuffer->Bind();
		RenderCommand::Clear();
		if (Camera::GetMainCamera() != nullptr) {
			Renderer::BeginScene();
			context->OnUpdate();
			Renderer::EndScene();
		}
		gameViewFramebuffer->Unbind();
	}
}