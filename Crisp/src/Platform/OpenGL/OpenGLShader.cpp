#include "CrispPCH.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Crisp {
	static GLenum ShaderTypeFromString(const std::string& type) {
		if (type == "vertex" || type == "vert") return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "frag" || type == "pixel") return GL_FRAGMENT_SHADER;

		CRISP_CORE_ASSERT(false, "Unkown shader type.");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& path) {
		CRISP_PROFILE_FUNCTION();

		std::string source = ReadFile(path);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);

		// Get name from file name
		auto lastSlash = path.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = path.rfind('.');
		auto count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
		name = path.substr(lastSlash, lastDot);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource) : name(name) {
		CRISP_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSource;
		sources[GL_FRAGMENT_SHADER] = fragmentSource;
		Compile(sources);
	}

	OpenGLShader::~OpenGLShader() {
		CRISP_PROFILE_FUNCTION();

		glDeleteProgram(rendererID);
	}

	void OpenGLShader::Bind() const {
		CRISP_PROFILE_FUNCTION();

		glUseProgram(rendererID);
	}

	void OpenGLShader::Unbind() const {
		CRISP_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	void OpenGLShader::SetUniformInt(const std::string& name, int value) {
		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& value) {
		UploadUniformMat4(name, value);
	}

	void OpenGLShader::SetUniformVec2(const std::string& name, const glm::vec2& value) {
		UploadUniformVec2(name, value);
	}

	void OpenGLShader::SetUniformVec3(const std::string& name, const glm::vec3& value) {
		UploadUniformVec3(name, value);
	}

	void OpenGLShader::SetUniformVec4(const std::string& name, const glm::vec4& value) {
		UploadUniformVec4(name, value);
	}

	void OpenGLShader::UploadUniformBool(const std::string& name, bool value) {
		glUniform1i(GetUniformLocation(name), (int)value);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value) {
		glUniform1i(GetUniformLocation(name), value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value) {
		glUniform1f(GetUniformLocation(name), value);
	}

	void OpenGLShader::UploadUniformVec2(const std::string& name, const glm::vec2& value) {
		glUniform2f(GetUniformLocation(name), value.x, value.y);
	}

	void OpenGLShader::UploadUniformVec3(const std::string& name, const glm::vec3& value) {
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformVec4(const std::string& name, const glm::vec4& value) {
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& value) {
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& value) {
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	std::string OpenGLShader::ReadFile(const std::string& path) {
		CRISP_PROFILE_FUNCTION();

		std::string result;
		std::ifstream in(path, std::ios::in | std::ios::binary);
		if (in) {
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else {
			CRISP_CORE_ERROR("Failed to open file at: {0}", path);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source) {
		CRISP_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos);
			CRISP_CORE_ASSERT(eol != std::string::npos, "Syntax Error.");

			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {
		CRISP_PROFILE_FUNCTION();

		GLuint program = glCreateProgram();
		CRISP_CORE_ASSERT(shaderSources.size() <= 2, "Only support upto 2 shaders currently");
		std::array<GLenum, 2> glShaderIDS;
		int glShaderIDindex = 0;

		for (auto& value : shaderSources) {
			GLenum type = value.first;
			const std::string& source = value.second;
		
			// Create an empty shader handle of type
			GLuint shader = glCreateShader(type);
			// Send the vertex shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* shaderSource = source.c_str();
			glShaderSource(shader, 1, &shaderSource, 0);
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE) {
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				CRISP_CORE_ERROR("{0}", infoLog.data());
				CRISP_CORE_ASSERT(false, "Shader compilation error.");
				break;
			}

			// Attach our shaders to our program
			glAttachShader(program, shader);
			glShaderIDS[glShaderIDindex++] = shader;
		}

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);

			for (auto id : glShaderIDS)
				glDeleteShader(id);

			// Use the infoLog as you see fit.
			CRISP_CORE_ERROR("{0}", infoLog.data());
			CRISP_CORE_ASSERT(false, "Shader linking error.");

			// In this simple program, we'll just leave
			return;
		}

		for (auto id : glShaderIDS)
			glDetachShader(program, id);

		// Set to rendererID as the shader is valid
		rendererID = program;
	}

	int OpenGLShader::GetUniformLocation(const std::string& name) {
		// Check if it does NOT exist in cache. If not finds and stores in cache
		if (uniformLocationCache.find(name) == uniformLocationCache.end())
			uniformLocationCache[name] = glGetUniformLocation(rendererID, name.c_str());
		return uniformLocationCache[name];
	}
}