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
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override { CRISP_CORE_ASSERT("Index is out of bounds", index < colorAttachments.size()); return colorAttachments[index]; }
		virtual const FrameBufferProperties& GetProperties() const override { return properties; }
	private:
		uint32_t rendererID = 0;
		FrameBufferProperties properties;

		std::vector<FrameBufferTextureProperties> colorAttachmentProperties;
		FrameBufferTextureProperties depthAttachmentProperties = FrameBufferTextureFormat::None;
	
		std::vector<uint32_t> colorAttachments;
		uint32_t depthAttachment = 0;
	};
}
