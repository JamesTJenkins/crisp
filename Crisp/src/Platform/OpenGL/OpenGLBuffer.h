#pragma once
#include "Crisp/Renderer/Buffer.h"

namespace Crisp {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer() override;

		OpenGLVertexBuffer(const OpenGLVertexBuffer& other) = delete;				// Copy construct
		OpenGLVertexBuffer& operator=(const OpenGLVertexBuffer& other) = delete;	// Copy assign

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return layout; }
		virtual void SetLayout(const BufferLayout& _layout) override { layout = _layout; }

		virtual void SetData(const void* data, uint32_t size) override;
	private:
		uint32_t rendererID;
		BufferLayout layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override { return count; }
	private:
		uint32_t rendererID;
		uint32_t count;
	};
}

