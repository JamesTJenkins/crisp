#pragma once
#include <string>

namespace Crisp {
	class Shader {
	public:
		Shader(const std::string& vertex, const std::string& fragment);
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t rendererID;
	};
}