#include "OpenGLVertexArray.hpp"
#include <stdint.h>

// Stop compiler warning from (const void*)offset
#define INT2VOIDP(i) (void*)(uintptr_t)(i)

namespace Crisp::Core {
    OpenGLVertexArray::OpenGLVertexArray() {
        glGenVertexArrays(1, &rendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray() {
        glDeleteVertexArrays(1, &rendererID);
    }

    void OpenGLVertexArray::CreateBuffer(const OpenGLVertexBuffer& vertexBuffer, const OpenGLVertexBufferLayout& layout) {
        Bind();
        vertexBuffer.Bind();
        const auto& elements = layout.GetElements();
        unsigned int offset = 0;
        for (unsigned int i = 0; i < elements.size(); i++) {
            const auto& element = elements[i];
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), INT2VOIDP(offset));
            offset += element.count * VertexBufferElement::GetTypeSize(element.type);
        }
    }

    void OpenGLVertexArray::Bind() const {
        glBindVertexArray(rendererID);
    }

    void OpenGLVertexArray::Unbind() const {
        glBindVertexArray(0);
    }
}  // namespace Crisp::Core