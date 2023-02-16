#include "CrispPCH.h"
#include "Renderer.h"

#include "Crisp/Components/Camera.h"

#include "VertexArray.h"

// TODO: CLEANUP THIS

namespace Crisp {
    Scope<Renderer::SceneData> Renderer::sceneData = CreateScope<Renderer::SceneData>();

    // TEMP
    struct QuadVertex {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 Texcoord;
        float TextureIndex;
    };

    struct RendererStorage {
        // Max per draw call
        static const uint32_t maxQuads = 10000;
        static const uint32_t maxVerts = maxQuads * 4;
        static const uint32_t maxIndices = maxQuads * 6;
        static const uint32_t maxTextureSlots = 32;    // TODO: query this

        Ref<VertexArray> quadVertexArray;
        Ref<VertexBuffer> quadVertexBuffer;
        Ref<Shader> textureShader;
        Ref<Texture2D> white;
        Ref<Sampler> textureSampler;
    
        uint32_t quadIndexCount = 0;
        QuadVertex* quadVertexBufferBase = nullptr;
        QuadVertex* quadVertexBufferPtr = nullptr;

        std::array<Ref<Texture2D>, maxTextureSlots> textureSlots;
        uint32_t textureSlotIndex = 1;  // 0 = white

        glm::vec4 QuadVertexPositions[4];

        Renderer::Statistics stats;
    };

    static RendererStorage storage;
    // TEMP

    void Renderer::Initialize() {
        CRISP_PROFILE_FUNCTION();

        RenderCommand::Initialize();

        storage.quadVertexArray = VertexArray::Create();

        storage.quadVertexBuffer = VertexBuffer::Create(storage.maxVerts * sizeof(QuadVertex));

        storage.quadVertexBuffer->SetLayout({
            { ShaderDataType::Vec3, "Position" },
            { ShaderDataType::Vec4, "Color" },
            { ShaderDataType::Vec2, "Texcoords" },
            { ShaderDataType::Float, "TextureIndex" }
        });
        storage.quadVertexArray->AddVertexBuffer(storage.quadVertexBuffer);

        storage.quadVertexBufferBase = new QuadVertex[storage.maxVerts];

        uint32_t* quadIndices = new uint32_t[storage.maxIndices];

        uint32_t offset = 0;
        for (uint32_t i = 0; i < storage.maxIndices; i += 6) {
            quadIndices[i + 0] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;

            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;

            offset += 4;
        }

        Ref<IndexBuffer> quadIndexBuffer = IndexBuffer::Create(quadIndices, storage.maxIndices);
        storage.quadVertexArray->SetIndexBuffer(quadIndexBuffer);
        delete[] quadIndices;

        storage.white = Texture2D::Create(1, 1);
        uint32_t whiteData = 0xffffffff;
        storage.white->SetData(&whiteData, sizeof(uint32_t));

        storage.textureSampler = Sampler::Create();
        storage.textureSampler->Bind();

        int32_t samplers[storage.maxTextureSlots];
        for (uint32_t i = 0; i < storage.maxTextureSlots; i++)
            samplers[i] = i;

        storage.textureShader = Shader::Create("assets/shaders/texture.glsl");
        storage.textureShader->Bind();
        storage.textureShader->SetUniformIntArray("u_Textures", samplers, storage.maxTextureSlots);

        storage.textureSlots[0] = storage.white;

        storage.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
        storage.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
        storage.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
        storage.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
    }

    void Renderer::Shutdown() {
        CRISP_PROFILE_FUNCTION();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
        CRISP_PROFILE_FUNCTION();

        RenderCommand::SetViewport(0, 0, width, height);
    }

    void Renderer::BeginScene() {
        CRISP_PROFILE_FUNCTION();

        sceneData->viewProjectionMatrix = Camera::GetMainCamera()->GetViewProjectionMatrix();
        storage.textureShader->Bind();
        storage.textureShader->SetUniformMat4("u_ViewProjection", sceneData->viewProjectionMatrix);

        storage.quadIndexCount = 0;
        storage.quadVertexBufferPtr = storage.quadVertexBufferBase;

        storage.textureSlotIndex = 1;
    }

    void Renderer::EndScene() {
        CRISP_PROFILE_FUNCTION();

        uint32_t dataSize = (uint8_t*)storage.quadVertexBufferPtr - (uint8_t*)storage.quadVertexBufferBase;
        storage.quadVertexBuffer->SetData(storage.quadVertexBufferBase, dataSize);

        Flush();
    }

    void Renderer::Flush() {
        for (uint32_t i = 0; i < storage.textureSlotIndex; i++)
            storage.textureSlots[i]->Bind(i);

        RenderCommand::DrawIndexed(storage.quadVertexArray, storage.quadIndexCount);
        storage.stats.DrawCalls++;
    }

    void Renderer::DrawQuad(const glm::mat4& transform, const glm::vec4& color) {
        CRISP_PROFILE_FUNCTION();

        if (storage.quadIndexCount >= storage.maxIndices)
            FlushAndReset();

        const float texture = 0.0f;

        storage.quadVertexBufferPtr->Position = transform * storage.QuadVertexPositions[0];
        storage.quadVertexBufferPtr->Color = color;
        storage.quadVertexBufferPtr->Texcoord = {  1.0f,  0.0f };
        storage.quadVertexBufferPtr->TextureIndex = texture;
        storage.quadVertexBufferPtr++;

        storage.quadVertexBufferPtr->Position = transform * storage.QuadVertexPositions[1];
        storage.quadVertexBufferPtr->Color = color;
        storage.quadVertexBufferPtr->Texcoord = { 0.0f, 0.0f };
        storage.quadVertexBufferPtr->TextureIndex = texture;
        storage.quadVertexBufferPtr++;

        storage.quadVertexBufferPtr->Position = transform * storage.QuadVertexPositions[2];
        storage.quadVertexBufferPtr->Color = color;
        storage.quadVertexBufferPtr->Texcoord = { 0.0f, 1.0f };
        storage.quadVertexBufferPtr->TextureIndex = texture;
        storage.quadVertexBufferPtr++;

        storage.quadVertexBufferPtr->Position = transform * storage.QuadVertexPositions[3];
        storage.quadVertexBufferPtr->Color = color;
        storage.quadVertexBufferPtr->Texcoord = { 1.0f, 1.0f };
        storage.quadVertexBufferPtr->TextureIndex = texture;
        storage.quadVertexBufferPtr++;

        storage.quadIndexCount += 6;
    
        storage.stats.QuadCount++;
    }

    void Renderer::DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture) {
        CRISP_PROFILE_FUNCTION();

        if (storage.quadIndexCount >= storage.maxIndices)
            FlushAndReset();

        constexpr glm::vec4 color = { 1.0f,1.0f,1.0f,1.0f };
        float textureIndex = 0.0f;

        for (uint32_t i = 1; i < storage.textureSlotIndex; i++) {
            // TODO: Fix this mess
            if (*storage.textureSlots[i].get() == *texture.get()) {
                textureIndex = (float)i;
                break;
            }
        }
        
        if (textureIndex == 0.0f) {
            textureIndex = (float)storage.textureSlotIndex;
            storage.textureSlots[storage.textureSlotIndex] = texture;
            storage.textureSlotIndex++;
        }

        storage.quadVertexBufferPtr->Position = transform * storage.QuadVertexPositions[0];
        storage.quadVertexBufferPtr->Color = color;
        storage.quadVertexBufferPtr->Texcoord = { 1.0f,  0.0f };
        storage.quadVertexBufferPtr->TextureIndex = textureIndex;
        storage.quadVertexBufferPtr++;

        storage.quadVertexBufferPtr->Position = transform * storage.QuadVertexPositions[1];
        storage.quadVertexBufferPtr->Color = color;
        storage.quadVertexBufferPtr->Texcoord = { 0.0f, 0.0f };
        storage.quadVertexBufferPtr->TextureIndex = textureIndex;
        storage.quadVertexBufferPtr++;

        storage.quadVertexBufferPtr->Position = transform * storage.QuadVertexPositions[2];
        storage.quadVertexBufferPtr->Color = color;
        storage.quadVertexBufferPtr->Texcoord = { 0.0f, 1.0f };
        storage.quadVertexBufferPtr->TextureIndex = textureIndex;
        storage.quadVertexBufferPtr++;

        storage.quadVertexBufferPtr->Position = transform * storage.QuadVertexPositions[3];
        storage.quadVertexBufferPtr->Color = color;
        storage.quadVertexBufferPtr->Texcoord = { 1.0f, 1.0f };
        storage.quadVertexBufferPtr->TextureIndex = textureIndex;
        storage.quadVertexBufferPtr++;

        storage.quadIndexCount += 6;

        storage.stats.QuadCount++;
    }

    void Renderer::DrawQuad(const glm::mat4& transform, const Ref<SubTexture2D>& subTexture) {
        CRISP_PROFILE_FUNCTION();

        if (storage.quadIndexCount >= storage.maxIndices)
            FlushAndReset();

        constexpr glm::vec4 color = { 1.0f,1.0f,1.0f,1.0f };
        constexpr size_t quadVertexCount = 4;
        float textureIndex = 0.0f;
        const glm::vec2* textureCoords = subTexture->GetTexCoords();
        const Ref<Texture2D> texture = subTexture->GetTexture();

        for (uint32_t i = 1; i < storage.textureSlotIndex; i++) {
            // TODO: Fix this mess
            if (*storage.textureSlots[i].get() == *texture.get()) {
                textureIndex = (float)i;
                break;
            }
        }

        if (textureIndex == 0.0f) {
            textureIndex = (float)storage.textureSlotIndex;
            storage.textureSlots[storage.textureSlotIndex] = texture;
            storage.textureSlotIndex++;
        }

        for (size_t i = 0; i < quadVertexCount; i++) {
            storage.quadVertexBufferPtr->Position = transform * storage.QuadVertexPositions[i];
            storage.quadVertexBufferPtr->Color = color;
            storage.quadVertexBufferPtr->Texcoord = textureCoords[i];
            storage.quadVertexBufferPtr->TextureIndex = textureIndex;
            storage.quadVertexBufferPtr++;
        }

        storage.quadIndexCount += 6;

        storage.stats.QuadCount++;
    }

    Renderer::Statistics Renderer::GetStats() {
        return storage.stats;
    }

    void Renderer::ResetStatistics() {
        memset(&storage.stats, 0, sizeof(Statistics));
    }

    void Renderer::FlushAndReset() {
        EndScene();

        storage.quadIndexCount = 0;
        storage.quadVertexBufferPtr = storage.quadVertexBufferBase;

        storage.textureSlotIndex = 1;
    }
}