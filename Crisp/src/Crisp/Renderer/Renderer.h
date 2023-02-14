#pragma once
#include "Crisp/Renderer/RenderCommand.h"
#include "Crisp/Renderer/Shader.h"
#include "Crisp/Renderer/Texture.h"

namespace Crisp {
	class Renderer {
	public:
		static void Initialize();
		static void Shutdown();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene();
		static void EndScene();
		static void Flush();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		// Primitives

		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D> texture);
		
		// Stats
		struct Statistics {
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};

		static Statistics GetStats();
		static void ResetStatistics();
	private:
		static void FlushAndReset();

		// TODO: fix this
		struct SceneData {
			glm::mat4 viewProjectionMatrix;
		};

		static Scope<SceneData> sceneData;
	};
}
