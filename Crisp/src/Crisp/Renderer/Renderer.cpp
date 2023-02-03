#include "CrispPCH.h"
#include "Renderer.h"

#include "Crisp/Components/Camera.h"

namespace Crisp {
    Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData;

    void Renderer::BeginScene() {
        sceneData->viewProjectionMatrix = Camera::GetMainCamera()->GetViewProjectionMatrix();
    }

    void Renderer::EndScene() {
    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray) {
        shader->Bind();
        shader->UploadUniformMat4("vp", sceneData->viewProjectionMatrix);
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}