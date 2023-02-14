#include "CrispPCH.h"
#include "FrameBuffer.h"

#include "Crisp/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Crisp {
	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferProperties& properties) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			CRISP_CORE_ASSERT(false, "RendererAPI::None isnt supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLFrameBuffer>(properties);
		}

		CRISP_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}
}