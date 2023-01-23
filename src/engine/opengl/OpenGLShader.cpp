#include "OpenGLShader.hpp"
#include "OpenGLDebugExtended.hpp"
#include <gtc/type_ptr.hpp>

namespace Crisp::Core {
    OpenGLShader::OpenGLShader(ShaderImport& shader) {
        GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
        // Set vertex source code
        const char* data = shader.vertexShader.ReadBinaryData();
        GLCall(glShaderSource(vertex, 1, &data, NULL));
        // Compile vertex shader
        GLCall(glCompileShader(vertex));
        // Error checks
        GLint vShaderCompiled = GL_FALSE;
        GLCall(glGetShaderiv(vertex, GL_COMPILE_STATUS, &vShaderCompiled));
        if (vShaderCompiled != GL_TRUE) {
            std::cout << "Unable to compile vertex shader: " << vertex << std::endl;
            PrintShaderLog(vertex);
            return;
        }

        // Create shader program and add to openGL shader list
        programID = glCreateProgram();
        // Attach vertex shader to program
        GLCall(glAttachShader(programID, vertex));

        // Fragment
        GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
        // Set fragment source code
        data = shader.fragmentShader.ReadBinaryData();
        GLCall(glShaderSource(fragment, 1, &data, NULL));
        // Compile fragment shader
        GLCall(glCompileShader(fragment));
        // Error checks
        GLint fShaderCompiled = GL_FALSE;
        GLCall(glGetShaderiv(fragment, GL_COMPILE_STATUS, &fShaderCompiled));
        if (fShaderCompiled != GL_TRUE) {
            std::cout << "Unable to compile fragment shader: " << fragment << std::endl;
            PrintShaderLog(fragment);
            // Cleanup
            GLCall(glDeleteShader(vertex));
            GLCall(glDeleteProgram(programID));
            programID = 0;
            return;
        }

        // Attach to program
        GLCall(glAttachShader(programID, fragment));
        // Link
        GLCall(glLinkProgram(programID));
        // Error check
        GLint programSuccess = GL_TRUE;
        GLCall(glGetProgramiv(programID, GL_LINK_STATUS, &programSuccess));
        if (programSuccess != GL_TRUE) {
            std::cout << "Error linking to program: " << programID << std::endl;
            PrintProgramLog(programID);
            // Cleanup
            GLCall(glDeleteShader(vertex));
            GLCall(glDeleteShader(fragment));
            GLCall(glDeleteProgram(programID));
            programID = 0;
            return;
        }

        // Cleanup excess shader references
        GLCall(glDeleteShader(vertex));
        GLCall(glDeleteShader(fragment));
    }

    OpenGLShader::~OpenGLShader() {
        GLCall(glDeleteProgram(programID));
    }

    void OpenGLShader::Bind() const {
        GLCall(glUseProgram(programID));
    }

    void OpenGLShader::Unbind() const {
        GLCall(glUseProgram(0));
    }

    void OpenGLShader::SetBool(const std::string &name, bool value) {
        GLCall(glUniform1i(GetUniformLocation(name), (int)value));
    }
    
    void OpenGLShader::SetInt(const std::string &name, int value) {
        GLCall(glUniform1i(GetUniformLocation(name), value));
    }
    
    void OpenGLShader::SetFloat(const std::string &name, float value) {
        GLCall(glUniform1i(GetUniformLocation(name), value));
    }

    void OpenGLShader::SetVec3(const std::string &name, glm::vec3 value) {
        GLCall(glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(value)));
    }

    void OpenGLShader::SetMat4(const std::string &name, glm::mat4 value) {
        GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)));
    }

    int OpenGLShader::GetUniformLocation(const std::string &name) {
        // Check if it does NOT exist in cache. If not finds and stores in cache
        if (uniformLocationCache.find(name) == uniformLocationCache.end())
            GLCall(uniformLocationCache[name] = glGetUniformLocation(programID, name.c_str()));
        return uniformLocationCache[name];
    }
}