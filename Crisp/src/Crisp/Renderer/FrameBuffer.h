#pragma once
#include "Crisp/Core/Core.h"

namespace Crisp {
	struct FrameBufferProperties {
		uint32_t width, height;
		uint32_t samples = 1;
		bool swapChainTarget = false;
	};

	class FrameBuffer {
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetColorAttachmentRendererID() const = 0;
		virtual const FrameBufferProperties& GetProperties() const = 0;

		static Ref<FrameBuffer> Create(const FrameBufferProperties& properties);
	};
}
