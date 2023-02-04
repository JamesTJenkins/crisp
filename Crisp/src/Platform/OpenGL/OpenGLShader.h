#pragma once
#include "Crisp/Renderer/Shader.h"

#include <glm/glm.hpp>
#include <unordered_map>

namespace Crisp {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		~OpenGLShader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformBool(const std::string& name, const bool& value);

		void UploadUniformInt(const std::string& name, const int& value);

		void UploadUniformFloat(const std::string& name, const float& value);
		void UploadUniformVec2(const std::string& name, const glm::vec2& value);
		void UploadUniformVec3(const std::string& name, const glm::vec3& value);
		void UploadUniformVec4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& value);
		void UploadUniformMat4(const std::string& name, const glm::mat4& value);
	private:
		uint32_t rendererID;
	private:
		int GetUniformLocation(const std::string& name);
		std::unordered_map<std::string, int> uniformLocationCache;
	};
}
