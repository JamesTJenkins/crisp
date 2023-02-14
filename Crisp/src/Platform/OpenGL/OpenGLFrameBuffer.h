#pragma once
#include "Crisp/Renderer/FrameBuffer.h"

namespace Crisp {
	class OpenGLFrameBuffer : public FrameBuffer {
	public:
		OpenGLFrameBuffer(const FrameBufferProperties& properties);
		virtual ~OpenGLFrameBuffer();

		OpenGLFrameBuffer(const OpenGLFrameBuffer& other) = delete;				// Copy construct
		OpenGLFrameBuffer& operator=(const OpenGLFrameBuffer& other) = delete;	// Copy assign

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return colorAttachment; }
		virtual const FrameBufferProperties& GetProperties() const override { return properties; }
	private:
		uint32_t rendererID = 0;
		uint32_t colorAttachment = 0, depthAttachment = 0;
		FrameBufferProperties properties;
	};
}
