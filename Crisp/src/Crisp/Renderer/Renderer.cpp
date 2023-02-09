#include "CrispPCH.h"
#include "Renderer.h"

#include "Crisp/Components/Camera.h"

#include "VertexArray.h"

namespace Crisp {
    Scope<Renderer::SceneData> Renderer::sceneData = CreateScope<Renderer::SceneData>();

    // TEMP
    struct RendererStorage {
        Ref<VertexArray> vertexArray;
        Ref<Shader> shader;
        glm::vec4 color;
    };

    static RendererStorage* storage;
    // TEMP

    void Renderer::Initialize() {
        RenderCommand::Initialize();

        storage = new RendererStorage();
        storage->color = glm::vec4(1, 1, 1, 1);

        storage->vertexArray = VertexArray::Create();

        float verts[3 * 4] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };

        Ref<VertexBuffer> vertexBuffer;
        vertexBuffer = VertexBuffer::Create(verts, sizeof(verts));

        BufferLayout layout = {
            { ShaderDataType::Vec3, "Position" }
        };
        vertexBuffer->SetLayout(layout);
        storage->vertexArray->AddVertexBuffer(vertexBuffer);

        unsigned int ind[6] = {
            0,1,2,
            2,3,0
        };

        Ref<IndexBuffer> indexBuffer;
        indexBuffer = IndexBuffer::Create(ind, sizeof(ind) / sizeof(uint32_t));
        storage->vertexArray->SetIndexBuffer(indexBuffer);

        storage->shader = Shader::Create("assets/shaders/FlatColor.glsl");
    }

    void Renderer::Shutdown() {
        delete storage;
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    void Renderer::BeginScene() {
        sceneData->viewProjectionMatrix = Camera::GetMainCamera()->GetViewProjectionMatrix();
        storage->shader->Bind();
        storage->shader->SetUniformMat4("vp", sceneData->viewProjectionMatrix);
    }

    void Renderer::EndScene() {
    }

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {
        shader->Bind();
        // TEMP
        shader->SetUniformMat4("vp", sceneData->viewProjectionMatrix);
        shader->SetUniformMat4("transform", transform);
        // TEMP
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer::DrawQuad(const glm::mat4& transform) {
        // TEMP
        storage->shader->Bind();
        storage->shader->SetUniformVec4("u_Color", storage->color);
        storage->shader->SetUniformMat4("transform", transform);

        storage->vertexArray->Bind();
        RenderCommand::DrawIndexed(storage->vertexArray);
        // TEMP
    }
}