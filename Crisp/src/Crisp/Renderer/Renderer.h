#pragma once
#include "Crisp/Renderer/RenderCommand.h"
#include "Crisp/Renderer/Shader.h"
#include "Crisp/Renderer/Texture.h"
#include "Crisp/Renderer/SubTexture.h"
#include "Crisp/Components/Camera.h"
#include "Crisp/Components/SpriteRenderer.h"

namespace Crisp {
	class Renderer {
	public:
		static void Initialize();
		static void Shutdown();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene();
		static void BeginScene(const Camera& camera);
		static void EndScene();
		static void Flush();

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		// Primitives
		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color, int entityID = -1);
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, int entityID = -1);
		static void DrawQuad(const glm::mat4& transform, const Ref<SubTexture2D>& subTexture);
		
		static void DrawSprite(const glm::mat4& transform, SpriteRenderer& src, int entityID);

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
