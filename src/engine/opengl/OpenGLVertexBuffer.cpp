#include "OpenGLVertexBuffer.hpp"

namespace Crisp::Core {
    OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, unsigned int size) {
        GLCall(glGenBuffers(1, &rendererID));
        Bind();
        GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    }
    
    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        GLCall(glDeleteBuffers(1, &rendererID));
    }

    void OpenGLVertexBuffer::Bind() const {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
    }

    void OpenGLVertexBuffer::Unbind() const {
        GLCall(glBindBuffer(0, 0));
    }
}