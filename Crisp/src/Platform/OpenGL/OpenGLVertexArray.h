#pragma once
#include "Crisp/Renderer/VertexArray.h"

namespace Crisp {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray() override;

		OpenGLVertexArray(const OpenGLVertexArray& other) = delete;				// Copy construct
		OpenGLVertexArray& operator=(const OpenGLVertexArray& other) = delete;	// Copy assign

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& _indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffer() const override { return vertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return indexBuffer; }
	private:
		uint32_t rendererID;
		uint32_t vertexBufferIndex = 0;
		std::vector<Ref<VertexBuffer>> vertexBuffers;
		Ref<IndexBuffer> indexBuffer;
	};
}

