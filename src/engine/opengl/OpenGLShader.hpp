#pragma once
#include <string>
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <../glm_common.hpp>
#include "../Material.hpp"

namespace Crisp::Core {
    class OpenGLShader {
    public:
        // Make this import and init
        OpenGLShader(ShaderImport& shader);
        // Make this cleanup
        ~OpenGLShader();
      
        void Use();
        // Util
        void SetBool(const std::string &name, bool value) const;
        void SetInt(const std::string &name, int value) const;
        void SetFloat(const std::string &name, float value) const;
        void SetVec3(const std::string &name, glm::vec3 value) const;
        void SetMat4(const std::string &name, glm::mat4 value) const;
        
        GLuint programID;
    };
}  // namespace Crisp::Core