#pragma once
#include "Crisp/Core/Core.h"

namespace Crisp {
	enum class FrameBufferTextureFormat {
		None = 0,
		// Color
		RGBA8,
		RINT,
		// Depth/Stencil
		DEPTH24STENCIL8,
	};

	struct FrameBufferTextureProperties {
		FrameBufferTextureProperties() = default;
		FrameBufferTextureProperties(FrameBufferTextureFormat format) : TextureFormat(format) {}
	
		FrameBufferTextureFormat TextureFormat = FrameBufferTextureFormat::None;
		// TODO: filter/wrap
	};

	struct FrameBufferAttachmentProperties {
		FrameBufferAttachmentProperties() = default;
		FrameBufferAttachmentProperties(std::initializer_list<FrameBufferTextureProperties> attachments) : attachments(attachments) {}

		std::vector<FrameBufferTextureProperties> attachments;
	};

	struct FrameBufferProperties {
		uint32_t width, height;
		FrameBufferAttachmentProperties attachment;
		uint32_t samples = 1;
		bool swapChainTarget = false;
	};

	class FrameBuffer {
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;

		virtual void ClearAttachment(uint32_t attachmentIndex, const int value) = 0;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;
		virtual const FrameBufferProperties& GetProperties() const = 0;

		static Ref<FrameBuffer> Create(const FrameBufferProperties& properties);
		static bool IsDepthFormat(FrameBufferTextureFormat format);
	};
}
