#pragma once
#include "Crisp.h"
#include <SDL.h>

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
		Ref<VertexArray> vertexArray;
		Ref<Shader> colorShader;
		Ref<FrameBuffer> framebuffer;
		Ref<Texture2D> texture;
		glm::vec4 color;

		Transform camTransform;
		Transform quadTransform;
		Transform quad1Transform;
		Camera* cam;
	};
}
