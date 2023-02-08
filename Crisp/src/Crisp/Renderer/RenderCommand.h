#pragma once
#include "Crisp/Renderer/RendererAPI.h"

namespace Crisp {
	class RenderCommand {
	public:
		inline static void Initialize() { rendererAPI->Initialize(); }

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { rendererAPI->SetViewport(x, y, width, height); }

		inline static void SetClearColor(const glm::vec4& color) { rendererAPI->SetClearColor(color); }
		inline static void Clear() { rendererAPI->Clear(); }

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) { rendererAPI->DrawIndexed(vertexArray); }
	private:
		static RendererAPI* rendererAPI;
	};
}