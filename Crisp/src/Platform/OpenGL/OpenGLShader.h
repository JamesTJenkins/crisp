#pragma once
#include "Crisp/Renderer/Shader.h"

#include <unordered_map>

#include <glm/glm.hpp>

// FIX
typedef unsigned int GLenum;

namespace Crisp {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& path);
		OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~OpenGLShader();

		OpenGLShader(const OpenGLShader& other) = delete;				// Copy construct
		OpenGLShader& operator=(const OpenGLShader& other) = delete;	// Copy assign

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const std::string& GetName() const override { return name; }

		void UploadUniformBool(const std::string& name, bool value);

		void UploadUniformInt(const std::string& name, int value);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformVec2(const std::string& name, const glm::vec2& value);
		void UploadUniformVec3(const std::string& name, const glm::vec3& value);
		void UploadUniformVec4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& value);
		void UploadUniformMat4(const std::string& name, const glm::mat4& value);
	private:
		std::string ReadFile(const std::string& path);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

		int GetUniformLocation(const std::string& name);
	private:
		std::unordered_map<std::string, int> uniformLocationCache;
		std::string name;
		uint32_t rendererID;
	};
}
