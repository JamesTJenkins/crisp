#include "CrispPCH.h"
#include "OpenGLFrameBuffer.h"

#include <glad/glad.h>

namespace Crisp {
	static GLenum TextureTarget(bool multisampled) {
		return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
	}

	static void CreateTextures(bool multisampled, uint32_t* outID, uint32_t count) {
		glCreateTextures(TextureTarget(multisampled), count, outID);
	}

	static void BindTexture(bool multisampled, uint32_t id) {
		glBindTexture(TextureTarget(multisampled), id);
	}

	static void AttachColorTexture(uint32_t id, int samples, GLenum format, uint32_t width, uint32_t height, int index) {
		bool multisampled = samples > 1;
		if (multisampled) {
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
		} else {
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

			// TODO: sort this out properly from framebuffer properties
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
	}

	static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height) {
		bool multisampled = samples > 1;
		if (multisampled) {
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
		} else {
			glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

			// TODO: sort this out properly from framebuffer properties
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
	}

	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferProperties& properties) : properties(properties) {
		CRISP_PROFILE_FUNCTION();

		for (auto format : properties.attachment.attachments) {
			if (!FrameBuffer::IsDepthFormat(format.TextureFormat))
				colorAttachmentProperties.emplace_back(format);
			else
				depthAttachmentProperties = format;
		}

		Invalidate();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer() {
		CRISP_PROFILE_FUNCTION();

		glDeleteFramebuffers(1, &rendererID);
		glDeleteTextures(colorAttachments.size(), colorAttachments.data());
		glDeleteTextures(1, &depthAttachment);
	}

	void OpenGLFrameBuffer::Invalidate() {
		CRISP_PROFILE_FUNCTION();

		// Delete any pre existing framebuffers
		if (rendererID) {
			glDeleteFramebuffers(1, &rendererID);
			glDeleteTextures(colorAttachments.size(), colorAttachments.data());
			glDeleteTextures(1, &depthAttachment);
			colorAttachments.clear();
			depthAttachment = 0;
		}

		// Recreate framebuffers
		glCreateFramebuffers(1, &rendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, rendererID);

		bool multisample = properties.samples > 1;

		if (colorAttachmentProperties.size()) {
			colorAttachments.resize(colorAttachmentProperties.size());
			CreateTextures(multisample, colorAttachments.data(), colorAttachments.size());

			for (size_t i = 0; i < colorAttachments.size(); i++) {
				BindTexture(multisample, colorAttachments[i]);
				switch (colorAttachmentProperties[i].TextureFormat) {
				case FrameBufferTextureFormat::RGBA8:
					AttachColorTexture(colorAttachments[i], properties.samples, GL_RGBA8, properties.width, properties.height, i);
					break;
				}
			}
		}

		if (depthAttachmentProperties.TextureFormat != FrameBufferTextureFormat::None) {
			CreateTextures(multisample, &depthAttachment, 1);
			BindTexture(multisample, depthAttachment);
			switch (depthAttachmentProperties.TextureFormat) {
			case FrameBufferTextureFormat::DEPTH24STENCIL8:
				AttachDepthTexture(depthAttachment, properties.samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, properties.width, properties.height);
				break;
			}
		}

		if (colorAttachments.size() > 1) {
			CRISP_CORE_ASSERT("Over max set color attachments", colorAttachments.size() <= 4);
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(colorAttachments.size(), buffers);
		} else if (colorAttachments.empty()) {
			// For depth only passes
			glDrawBuffer(GL_NONE);
		}

		CRISP_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete.");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::Bind() {
		CRISP_PROFILE_FUNCTION();

		glBindFramebuffer(GL_FRAMEBUFFER, rendererID);
	}

	void OpenGLFrameBuffer::Unbind() {
		CRISP_PROFILE_FUNCTION();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height) {
		CRISP_PROFILE_FUNCTION();

		properties.width = width;
		properties.height = height;
		Invalidate();
	}
}