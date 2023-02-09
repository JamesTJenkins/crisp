#include "CrispPCH.h"
#include "Shader.h"

#include "Crisp/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Crisp {
	Ref<Shader> Shader::Create(const std::string& path) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			CRISP_CORE_ASSERT(false, "RendererAPI::None isnt supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLShader>(path);
		}

		CRISP_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			CRISP_CORE_ASSERT(false, "RendererAPI::None isnt supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLShader>(name, vertexSource, fragmentSource);
		}

		CRISP_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader) {
		auto& name = shader->GetName();
		CRISP_CORE_ASSERT(!Exists(name), "Shader already exists.");
		shaders[name] = shader;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader) {
		CRISP_CORE_ASSERT(!Exists(name), "Shader already exists.");
		shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& path) {
		auto shader = Shader::Create(path);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& path) {
		auto shader = Shader::Create(path);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name) {
		CRISP_CORE_ASSERT(Exists(name), "Shader not found");
		return shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const {
		return shaders.find(name) != shaders.end();
	}
}