#pragma once
#include "Crisp.h"
#include <SDL.h>

#include "Editor/SceneHierarchy.h"
#include "Editor/SceneProperties.h"
#include "Editor/StatisticsPanel.h"
#include "Editor/SceneWindow.h"
#include "Editor/GameWindow.h"

namespace Crisp {
	class EditorLayer : public Layer {
	public:
		EditorLayer();
		virtual ~EditorLayer() override;

		EditorLayer(const EditorLayer& other) = delete;				// Copy construct
		EditorLayer& operator=(const EditorLayer& other) = delete;	// Copy assign

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate() override;
		virtual void OnImGuiRender() override;

		virtual void OnEvent(const SDL_Event* e) override;
	private:
		void NewScene();
		void OpenScene();
		void SaveSceneAs();
	private:
		Ref<VertexArray> vertexArray;
		Ref<Shader> colorShader;
		Ref<Texture2D> texture;
		Ref<Scene> activeScene;

		// Editor
		SceneWindow sceneWindow;
		GameWindow gameWindow;
		SceneHierarchy hierarchy;
		SceneProperties properties;
		StatisticsPanel stats;
	};
}
