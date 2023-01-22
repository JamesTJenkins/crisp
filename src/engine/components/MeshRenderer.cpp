#include "MeshRenderer.hpp"

namespace Crisp::Core {
    MeshRenderer::MeshRenderer(Mesh* mesh, OpenGLMaterial* material) : mesh(mesh), material(material) {}
    MeshRenderer::~MeshRenderer() {}
}