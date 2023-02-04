#pragma once
#include "Crisp/Renderer/RenderCommand.h"
#include "Crisp/Renderer/Shader.h"

namespace Crisp {
	class Renderer {
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		// TODO: fix this
		struct SceneData {
			glm::mat4 viewProjectionMatrix;
		};

		static SceneData* sceneData;
	};
}