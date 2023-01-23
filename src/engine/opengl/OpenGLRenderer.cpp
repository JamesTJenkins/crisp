#include "OpenGLRenderer.hpp"
#include "OpenGLDebug.hpp"

namespace Crisp::Core {    
    void OpenGLRenderer::Draw(const OpenGLVertexArray& vertexArray, const OpenGLIndexBuffer& indexBuffer, const OpenGLShader& shader) const {
        shader.Bind();
        vertexArray.Bind();
        indexBuffer.Bind();
        GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr));
    }

    void OpenGLRenderer::Clear() {
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
    }
}