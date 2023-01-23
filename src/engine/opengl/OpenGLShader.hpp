#pragma once
#include <string>
#include <GL/glew.h>
#include <glm.hpp>
#include <unordered_map>
#include "../Import.hpp"

namespace Crisp::Core {
    class OpenGLShader {
    public:
        // Make this import and init
        OpenGLShader(ShaderImport& shader);
        // Make this cleanup
        ~OpenGLShader();
      
        void Bind() const;
        void Unbind() const;
        // Util
        void SetBool(const std::string &name, bool value);
        void SetInt(const std::string &name, int value);
        void SetFloat(const std::string &name, float value);
        void SetVec3(const std::string &name, glm::vec3 value);
        void SetMat4(const std::string &name, glm::mat4 value);
        
        unsigned int programID;
    private:
        int GetUniformLocation(const std::string &name);
        std::unordered_map<std::string, int> uniformLocationCache;
    };
}  // namespace Crisp::Core