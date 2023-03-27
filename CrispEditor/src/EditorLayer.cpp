#include "EditorLayer.h"
#include <imgui/imgui.h>

#include "Crisp/Scene/SceneSerializer.h"
#include "Crisp/Utils/PlatformUtils.h"

namespace Crisp {
	EditorLayer::EditorLayer() : Layer("EditorLayer") {}

	EditorLayer::~EditorLayer() {}

	void EditorLayer::OnAttach() {
		CRISP_PROFILE_FUNCTION();

		RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		texture = Texture2D::Create("assets/textures/bacon.png");

		activeScene = CreateRef<Scene>();
		hierarchy.SetContext(activeScene);
		sceneWindow.SetContext(activeScene);
		gameWindow.SetContext(activeScene);
	}

	void EditorLayer::OnDetach() {
		CRISP_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate() {
		CRISP_PROFILE_FUNCTION();

		// NEW, OPEN, SAVE scene hotkeys
		if (Input::IsKeyPressed(CRISP_LCTRL) || Input::IsKeyPressed(CRISP_RCTRL)) {
			if (Input::IsKeyPressed(CRISP_N))
				NewScene();
			else if (Input::IsKeyPressed(CRISP_O))
				OpenScene();
			else if (Input::IsKeyPressed(CRISP_S))
				SaveSceneAs();
		}

		sceneWindow.OnEditorUpdate();
		sceneWindow.SceneWindowDraw();

		// This needs to be after scene render loop otherwise it will give
		// stats for rendering both scene and game view
		Renderer::ResetStatistics();

		gameWindow.GameWindowDraw();
	}

	// TODO: Move code to seperate windows and tidy this up
	void EditorLayer::OnImGuiRender() {
		static bool dockspaceOpen = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen) {
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		} else {
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Crisp Dockspace", &dockspaceOpen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			ImGuiID dockspace_id = ImGui::GetID("Dockspace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("New Scene", "Ctrl+N")) {
					NewScene();
				}

				if (ImGui::MenuItem("Open Scene", "Ctrl+O")) {
					OpenScene();
				}

				if (ImGui::MenuItem("Save Scene", "Ctrl+S")) {
					SaveSceneAs();
				}

				if (ImGui::MenuItem("Exit"))
					Application::Get().Quit();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		hierarchy.OnImGuiRender();
		properties.OnImGuiRender();
		sceneWindow.OnImGuiRender();
		gameWindow.OnImGuiRender();
		stats.OnImGuiRender();

		ImGui::End();	// DOCKSPACE
	}

	void EditorLayer::OnEvent(const SDL_Event* e) {}

	void EditorLayer::NewScene() {
		activeScene = CreateRef<Scene>();
		// Setting these to 0 will force a reset to occur for both viewports 
		gameWindow.gameViewportSize.x = 0;
		sceneWindow.sceneViewportSize.x = 0;
		// There is no main camera on scene reset
		Camera::SetMainCamera(nullptr);

		hierarchy.SetContext(activeScene);
		sceneWindow.SetContext(activeScene);
		gameWindow.SetContext(activeScene);
	}

	void EditorLayer::OpenScene() {
		std::string filepath = FileDialog::OpenFile("Crisp Scene (*.crisp)\0*.crisp\0");
		if (!filepath.empty()) {
			NewScene();
			SceneSerializer serializer(activeScene);
			serializer.Deserialize(filepath);
		}
	}

	void EditorLayer::SaveSceneAs() {
		std::string filepath = FileDialog::SaveFile("Crisp Scene (*.crisp)\0*.crisp\0");
		if (!filepath.empty()) {
			SceneSerializer serializer(activeScene);
			serializer.Serialize(filepath);
		}
	}
}
