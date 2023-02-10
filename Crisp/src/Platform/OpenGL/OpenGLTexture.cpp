#include "CrispPCH.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

namespace Crisp {
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) : width(width), height(height) {
		CRISP_PROFILE_FUNCTION();

		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
		glTextureStorage2D(textureID, 1, internalFormat, width, height);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : path(path) {
		CRISP_PROFILE_FUNCTION();

		int _width, _height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = nullptr;
		{
			CRISP_PROFILE_SCOPE("OpenGLTexture2D::OpenGLTexture2D(const std::string& path) :: stbi_load");
			data = stbi_load(path.c_str(), &_width, &_height, &channels, 0);
		}
		CRISP_CORE_ASSERT(data, "Failed to load image.");

		GLenum _internalFormat = 0, _dataFormat = 0;
		if (channels == 4) {
			_internalFormat = GL_RGBA8;
			_dataFormat = GL_RGBA;
		} else if(channels == 3) {
			_internalFormat = GL_RGB8;
			_dataFormat = GL_RGB;
		}

		width = _width;
		height = _height;
		internalFormat = _internalFormat;
		dataFormat = _dataFormat;

		CRISP_CORE_ASSERT(internalFormat, "Image format not supported.");

		glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
		glTextureStorage2D(textureID, 1, internalFormat, width, height);
		glTextureSubImage2D(textureID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);
		glGenerateTextureMipmap(textureID);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		CRISP_PROFILE_FUNCTION();

		glDeleteTextures(1, &textureID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size) {
		CRISP_PROFILE_FUNCTION();

		uint32_t bpp = dataFormat == GL_RGBA ? 4 : 3;
		CRISP_CORE_ASSERT(size == width * height * bpp, "Data must be entire texture.");
		glTextureSubImage2D(textureID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const {
		CRISP_PROFILE_FUNCTION();

		glBindTextureUnit(slot, textureID);
	}

	OpenGLSampler::OpenGLSampler() {
		CRISP_PROFILE_FUNCTION();

		glCreateSamplers(1, &samplerID);

		glSamplerParameteri(samplerID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glSamplerParameteri(samplerID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		GLint maxAnisotropy;
		glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &maxAnisotropy);
		glSamplerParameteri(samplerID, GL_TEXTURE_MAX_ANISOTROPY, maxAnisotropy);
	}

	OpenGLSampler::~OpenGLSampler() {
		CRISP_PROFILE_FUNCTION();

		glDeleteSamplers(1, &samplerID);
	}

	void OpenGLSampler::Bind(uint32_t slot) const {
		CRISP_PROFILE_FUNCTION();

		glBindSampler(slot, samplerID);
	}
}