#pragma once
#include <GL/glew.h>

#include "OpenGLVertexArray.hpp"
#include "OpenGLIndexBuffer.hpp"
#include "OpenGLShader.hpp"

namespace Crisp::Core {
    class OpenGLRenderer {
    public:
        OpenGLRenderer() {}
        ~OpenGLRenderer() {}

        void Draw(const OpenGLVertexArray& vertexArray, const OpenGLIndexBuffer& indexBuffer, const OpenGLShader& shader) const;
        void Clear();
    };
}