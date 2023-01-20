#include "OpenGLShader.hpp"
#include "OpenGLDebug.hpp"

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

    void OpenGLShader::SetBool(const std::string &name, bool value) const {
    
    }
    
    void OpenGLShader::SetInt(const std::string &name, int value) const {
    
    }
    
    void OpenGLShader::SetFloat(const std::string &name, float value) const {
    
    }
}