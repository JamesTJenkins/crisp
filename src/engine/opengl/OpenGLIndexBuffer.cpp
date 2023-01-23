#include "OpenGLIndexBuffer.hpp"

namespace Crisp::Core {
    OpenGLIndexBuffer::OpenGLIndexBuffer(const unsigned int* data, unsigned int count) : count(count) {
        GLCall(glGenBuffers(1, &rendererID));
        Bind();
        // IF sizeof(unsigned int) is not 4 on a specific platform it could break horribly 
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
    }
    
    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        GLCall(glDeleteBuffers(1, &rendererID));
    }

    void OpenGLIndexBuffer::Bind() const {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
    }

    void OpenGLIndexBuffer::Unbind() const {
        GLCall(glBindBuffer(0, 0));
    }
}