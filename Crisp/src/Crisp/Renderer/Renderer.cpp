#include "CrispPCH.h"
#include "Renderer.h"

#include "Crisp/Components/Camera.h"

#include "VertexArray.h"

namespace Crisp {
    Scope<Renderer::SceneData> Renderer::sceneData = CreateScope<Renderer::SceneData>();

    // TEMP
    struct RendererStorage {
        Ref<VertexArray> vertexArray;
        Ref<Shader> textureShader;
        Ref<Texture2D> white;
    };

    static RendererStorage* storage;
    // TEMP

    void Renderer::Initialize() {
        CRISP_PROFILE_FUNCTION();

        RenderCommand::Initialize();

        storage = new RendererStorage();

        storage->vertexArray = VertexArray::Create();

        float verts[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f, 1.0f
        };

        Ref<VertexBuffer> vertexBuffer;
        vertexBuffer = VertexBuffer::Create(verts, sizeof(verts));

        BufferLayout layout = {
            { ShaderDataType::Vec3, "Position" },
            { ShaderDataType::Vec2, "Texcoords" }
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

        storage->white = Texture2D::Create(1, 1);
        uint32_t whiteData = 0xffffffff;
        storage->white->SetData(&whiteData, sizeof(uint32_t));

        storage->textureShader = Shader::Create("assets/shaders/texture.glsl");

        storage->textureShader->Bind();
        storage->textureShader->SetUniformInt("u_Texture", 0);
    }

    void Renderer::Shutdown() {
        CRISP_PROFILE_FUNCTION();

        delete storage;
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
        CRISP_PROFILE_FUNCTION();

        RenderCommand::SetViewport(0, 0, width, height);
    }

    void Renderer::BeginScene() {
        CRISP_PROFILE_FUNCTION();

        sceneData->viewProjectionMatrix = Camera::GetMainCamera()->GetViewProjectionMatrix();
        storage->textureShader->Bind();
        storage->textureShader->SetUniformMat4("u_ViewProjection", sceneData->viewProjectionMatrix);
    }

    void Renderer::EndScene() {
        CRISP_PROFILE_FUNCTION();
    }

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {
        CRISP_PROFILE_FUNCTION();

        shader->Bind();
        // TEMP
        shader->SetUniformMat4("u_ViewProjection", sceneData->viewProjectionMatrix);
        shader->SetUniformMat4("u_Transform", transform);
        // TEMP
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer::DrawQuad(const glm::mat4& transform, const glm::vec4& color) {
        CRISP_PROFILE_FUNCTION();

        // TEMP
        storage->textureShader->SetUniformMat4("u_Transform", transform);
        storage->textureShader->SetUniformVec4("u_Color", color);
        storage->textureShader->SetUniformVec2("u_Tiling", { 1,1 });

        storage->vertexArray->Bind();
        RenderCommand::DrawIndexed(storage->vertexArray);
        // TEMP
    }

    void Renderer::DrawQuad(const glm::mat4& transform, const Ref<Texture2D> texture) {
        CRISP_PROFILE_FUNCTION();

        // TEMP
        storage->textureShader->SetUniformMat4("u_Transform", transform);
        storage->textureShader->SetUniformVec4("u_Color", {1,1,1,1});
        storage->textureShader->SetUniformVec2("u_Tiling", { 2,2 });
        texture->Bind();
        storage->vertexArray->Bind();
        RenderCommand::DrawIndexed(storage->vertexArray);
        // TEMP
    }
}