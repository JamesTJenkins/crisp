#pragma once
#include "Crisp/Renderer/RenderCommand.h"
#include "Crisp/Renderer/Shader.h"

namespace Crisp {
	class Renderer {
	public:
		static void Initialize();
		static void Shutdown();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene();
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		// Primitives

		static void DrawQuad(const glm::mat4& transform = glm::mat4(1));
	private:
		// TODO: fix this
		struct SceneData {
			glm::mat4 viewProjectionMatrix;
		};

		static Scope<SceneData> sceneData;
	};
}
