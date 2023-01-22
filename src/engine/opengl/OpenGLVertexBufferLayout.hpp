#pragma once
#include <GL/glew.h>

#include <type_traits>
#include <vector>

namespace Crisp::Core {
    struct VertexBufferElement {
        unsigned int type;
        unsigned int count;
        unsigned char normalized;

        static unsigned int GetTypeSize(unsigned int type) {
            switch (type) {
                case GL_FLOAT:
                    return 4;
                case GL_UNSIGNED_INT:
                    return 4;
                case GL_UNSIGNED_BYTE:
                    return 1;
            }
            return 0;
        }
    };

    class OpenGLVertexBufferLayout {
       private:
        std::vector<VertexBufferElement> elements;
        unsigned int stride;

       public:
        OpenGLVertexBufferLayout() : stride(0) {}

        template <typename T>
        void Push(unsigned int count) {}

        inline const std::vector<VertexBufferElement>& GetElements() const { return elements; }
        inline unsigned int GetStride() const { return stride; }
    };

    // Must be outside class cause C++ standards are an ass

    template <>
    void OpenGLVertexBufferLayout::Push<float>(unsigned int count) {
        elements.push_back({GL_FLOAT, count, GL_FALSE});
        stride += count * VertexBufferElement::GetTypeSize(GL_FLOAT);
    }

    template <>
    void OpenGLVertexBufferLayout::Push<unsigned int>(unsigned int count) {
        elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        stride += count * VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT);
    }

    template <>
    void OpenGLVertexBufferLayout::Push<unsigned char>(unsigned int count) {
        elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        stride += count * VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE);
    }

}  // namespace Crisp::Core