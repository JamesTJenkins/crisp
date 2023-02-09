#include "CrispPCH.h"
#include "Crisp/Renderer/VertexArray.h"

#include "Crisp/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Crisp {
	Ref<VertexArray> VertexArray::Create() {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			CRISP_CORE_ASSERT(false, "RendererAPI::None isnt supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexArray>();
		}

		CRISP_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}
}