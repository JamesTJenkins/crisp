#pragma once
#include "../Mesh.hpp"
#include "../opengl/OpenGLMaterial.hpp"

namespace Crisp::Core {
    class MeshRenderer {
    public:
        MeshRenderer(Mesh* mesh, OpenGLMaterial* material, bool isStatic = false);
        ~MeshRenderer();

        Mesh* mesh;
        OpenGLMaterial* material;
        bool staticMesh;
    };
}