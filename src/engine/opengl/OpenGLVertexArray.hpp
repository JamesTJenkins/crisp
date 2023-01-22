#pragma once
#include "OpenGLVertexBuffer.hpp"
#include "OpenGLVertexBufferLayout.hpp"

namespace Crisp::Core {
    class OpenGLVertexArray {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        void CreateBuffer(const OpenGLVertexBuffer& vertexBuffer, const OpenGLVertexBufferLayout& layout);
    
        void Bind() const;
        void Unbind() const;
    private:
        unsigned int rendererID;
    };
}