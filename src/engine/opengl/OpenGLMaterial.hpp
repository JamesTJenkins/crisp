#pragma once
#include "OpenGLShader.hpp"

namespace Crisp::Core {
    class OpenGLMaterial {
    public:
        OpenGLMaterial(OpenGLShader* shader) : shader(shader) {} 
        ~OpenGLMaterial() {}

        OpenGLShader* shader;
    };
}