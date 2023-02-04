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

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform) {
        shader->Bind();
        shader->UploadUniformMat4("vp", sceneData->viewProjectionMatrix);
        shader->UploadUniformMat4("transform", transform);
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}