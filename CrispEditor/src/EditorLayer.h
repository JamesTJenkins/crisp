#pragma once
#include "Crisp.h"
#include <SDL.h>

#include "Editor/SceneHierarchy.h"
#include "Editor/SceneProperties.h"

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
		Ref<FrameBuffer> gameViewFramebuffer;
		Ref<FrameBuffer> sceneViewFramebuffer;

		Ref<VertexArray> vertexArray;
		Ref<Shader> colorShader;
		Ref<Texture2D> texture;
		Ref<Scene> activeScene;

		glm::vec2 sceneViewportSize;
		glm::vec2 gameViewportSize;
		bool sceneViewportFocused = false;
		bool gameViewportFocused = false;

		SceneCamera sceneCam;

		// Editor
		SceneHierarchy hierarchy;
		SceneProperties properties;
	};
}
