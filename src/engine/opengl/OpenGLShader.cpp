#include "OpenGLShader.hpp"
#include "OpenGLDebug.hpp"
#include <gtc/type_ptr.hpp>

namespace Crisp::Core {
    OpenGLShader::OpenGLShader(ShaderImport& shader) {
        GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
        // Set vertex source code
        const char* data = shader.vertexShader.ReadBinaryData();
        glShaderSource(vertex, 1, &data, NULL);
        // Compile vertex shader
        glCompileShader(vertex);
        // Error checks
        GLint vShaderCompiled = GL_FALSE;
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &vShaderCompiled);
        if (vShaderCompiled != GL_TRUE) {
            std::cout << "Unable to compile vertex shader: " << vertex << std::endl;
            PrintShaderLog(vertex);
            return;
        }

        // Create shader program and add to openGL shader list
        programID = glCreateProgram();
        // Attach vertex shader to program
        glAttachShader(programID, vertex);

        // Fragment
        GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
        // Set fragment source code
        data = shader.fragmentShader.ReadBinaryData();
        glShaderSource(fragment, 1, &data, NULL);
        // Compile fragment shader
        glCompileShader(fragment);
        // Error checks
        GLint fShaderCompiled = GL_FALSE;
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &fShaderCompiled);
        if (fShaderCompiled != GL_TRUE) {
            std::cout << "Unable to compile fragment shader: " << fragment << std::endl;
            PrintShaderLog(fragment);
            // Cleanup
            glDeleteShader(vertex);
            glDeleteProgram(programID);
            programID = 0;
            return;
        }

        // Attach to program
        glAttachShader(programID, fragment);
        // Link
        glLinkProgram(programID);
        // Error check
        GLint programSuccess = GL_TRUE;
        glGetProgramiv(programID, GL_LINK_STATUS, &programSuccess);
        if (programSuccess != GL_TRUE) {
            std::cout << "Error linking to program: " << programID << std::endl;
            PrintProgramLog(programID);
            // Cleanup
            glDeleteShader(vertex);
            glDeleteShader(fragment);
            glDeleteProgram(programID);
            programID = 0;
            return;
        }

        // Cleanup excess shader references
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(programID);
    }

    void OpenGLShader::Bind() {
        glUseProgram(programID);
    }

    void OpenGLShader::Unbind() {
        glUseProgram(0);
    }

    void OpenGLShader::SetBool(const std::string &name, bool value) const {
        glUniform1i(GetUniformLocation(name)), (int)value);
    }
    
    void OpenGLShader::SetInt(const std::string &name, int value) const {
        glUniform1i(GetUniformLocation(name)), value);
    }
    
    void OpenGLShader::SetFloat(const std::string &name, float value) const {
        glUniform1i(GetUniformLocation(name)), value);
    }

    void OpenGLShader::SetVec3(const std::string &name, glm::vec3 value) const {
        glUniform3fv(GetUniformLocation(name)), 1, glm::value_ptr(value));
    }

    void OpenGLShader::SetMat4(const std::string &name, glm::mat4 value) const {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    int GetUniformLocation(const std::string& name) {
        // Check if it does NOT exist in cache. If not finds and stores in cache
        if (uniformLocationCache.find(name) == uniformLocationCache.end())
            uniformLocationCache[name] = glGetUniformLocation(programID, name.c_str());
        return uniformLocationCache[name];
    }
}