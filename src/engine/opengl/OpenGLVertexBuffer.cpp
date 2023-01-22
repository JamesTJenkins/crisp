#include "OpenGLVertexBuffer.hpp"
#include <GL/glew.h>

namespace Crisp::Core {
    OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, unsigned int size) {
        glGenBuffers(1, &rendererID);
        Bind();
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }
    
    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        glDeleteBuffers(1, &rendererID);
    }

    void OpenGLVertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
    }

    void OpenGLVertexBuffer::Unbind() const {
        glBindBuffer(0, 0);
    }
}