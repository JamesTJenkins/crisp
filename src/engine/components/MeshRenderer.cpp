#include "MeshRenderer.hpp"

namespace Crisp::Core {
    MeshRenderer::MeshRenderer(Mesh* mesh, OpenGLMaterial* material, bool isStatic) : mesh(mesh), material(material), staticMesh(isStatic) {}
    MeshRenderer::~MeshRenderer() {}
}