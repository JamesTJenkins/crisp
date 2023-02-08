#include "CrispPCH.h"
#include "Texture.h"

#include "Crisp/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Crisp {
	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			CRISP_CORE_ASSERT(false, "RendererAPI::None isnt supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		}

		CRISP_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

	Ref<Sampler> Sampler::Create(){
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			CRISP_CORE_ASSERT(false, "RendererAPI::None isnt supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLSampler>();
		}

		CRISP_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}
}
