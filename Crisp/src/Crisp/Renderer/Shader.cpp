#include "CrispPCH.h"
#include "Shader.h"

#include "Crisp/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Crisp {
	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			CRISP_CORE_ASSERT(false, "RendererAPI::None isnt supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSource, fragmentSource);
		}

		CRISP_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}
}