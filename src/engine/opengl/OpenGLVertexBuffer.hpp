#pragma once
#include "OpenGLDebug.hpp"

namespace Crisp::Core {
    class OpenGLVertexBuffer {
    public:
        OpenGLVertexBuffer(const void* data, unsigned int size);
        ~OpenGLVertexBuffer();

        void Bind() const;
        void Unbind() const;
    private:
        unsigned int rendererID;
    };
}