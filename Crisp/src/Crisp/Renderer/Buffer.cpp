#include "CrispPCH.h"
#include "Crisp/Renderer/Buffer.h"

#include "Crisp/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Crisp {
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			CRISP_CORE_ASSERT(false, "RendererAPI::None isnt supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		CRISP_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			CRISP_CORE_ASSERT(false, "RendererAPI::None isnt supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLIndexBuffer>(indices, size);
		}

		CRISP_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}
}