#pragma once
#include "Crisp/Renderer/Texture.h"

namespace Crisp {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D() override;

		OpenGLTexture2D(const OpenGLTexture2D& other) = delete;				// Copy construct
		OpenGLTexture2D& operator=(const OpenGLTexture2D& other) = delete;	// Copy assign

		virtual uint32_t GetWidth() const override { return width; }
		virtual uint32_t GetHeight() const override { return height; }

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		std::string path;
		uint32_t width, height;
		uint32_t textureID, samplerID;
	};
}

