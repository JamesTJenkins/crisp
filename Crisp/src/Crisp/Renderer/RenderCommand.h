#pragma once
#include "Crisp/Renderer/RendererAPI.h"

namespace Crisp {
	class RenderCommand {
	public:
		inline static void SetClearColor(const glm::vec4& color) { rendererAPI->SetClearColor(color); }
		inline static void Clear() { rendererAPI->Clear(); }

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) { rendererAPI->DrawIndexed(vertexArray); }
	private:
		static RendererAPI* rendererAPI;
	};
}