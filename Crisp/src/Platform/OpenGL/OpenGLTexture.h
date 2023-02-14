#pragma once
#include "Crisp/Renderer/Texture.h"
#include <glad/glad.h>

namespace Crisp {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D() override;

		OpenGLTexture2D(const OpenGLTexture2D& other) = delete;				// Copy construct
		OpenGLTexture2D& operator=(const OpenGLTexture2D& other) = delete;	// Copy assign

		virtual uint32_t GetWidth() const override { return width; }
		virtual uint32_t GetHeight() const override { return height; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;

		virtual bool operator==(const Texture& other) const override { return textureID == ((OpenGLTexture2D&)other).textureID; };
	private:
		std::string path;
		uint32_t width, height;
		uint32_t textureID;
		GLenum internalFormat, dataFormat;
	};

	class OpenGLSampler : public Sampler {
	public:
		OpenGLSampler();
		virtual ~OpenGLSampler() override;

		OpenGLSampler(const OpenGLSampler& other) = delete;				// Copy construct
		OpenGLSampler& operator=(const OpenGLSampler& other) = delete;	// Copy assign

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		uint32_t samplerID;
	};
}

