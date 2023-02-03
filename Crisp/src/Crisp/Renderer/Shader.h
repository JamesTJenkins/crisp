#pragma once
#include <string>
#include <glm/glm.hpp>

namespace Crisp {
	class Shader {
	public:
		Shader(const std::string& vertex, const std::string& fragment);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		uint32_t rendererID;
	};
}