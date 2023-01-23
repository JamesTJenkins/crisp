#pragma once
#include "OpenGLDebug.hpp"

namespace Crisp::Core {
    class OpenGLIndexBuffer {
    public:
        OpenGLIndexBuffer(const unsigned int* data, unsigned int count);
        ~OpenGLIndexBuffer();

        void Bind() const;
        void Unbind() const;

        inline unsigned int GetCount() const { return count; }
    private:
        unsigned int rendererID;
        unsigned int count;
    };
}