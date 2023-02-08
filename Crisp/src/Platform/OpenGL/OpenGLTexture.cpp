#include "CrispPCH.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

#include <glad/glad.h>
#include <stdexcept>

namespace Crisp {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : path(path) {
		int _width, _height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &_width, &_height, &channels, 0);
		CRISP_CORE_ASSERT(data, "Failed to load image.");

		width = _width;
		height = _height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4) {
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		} else if(channels == 3) {
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		CRISP_CORE_ASSERT(internalFormat, "Image format not supported.");

		glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
		glTextureStorage2D(textureID, 1, internalFormat, width, height);
		glTextureSubImage2D(textureID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);
		glGenerateTextureMipmap(textureID);

		stbi_image_free(data);

		glCreateSamplers(1, &samplerID);

		glSamplerParameteri(samplerID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glSamplerParameteri(samplerID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		GLint maxAnisotropy;
		glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &maxAnisotropy);
		glSamplerParameteri(samplerID, GL_TEXTURE_MAX_ANISOTROPY, maxAnisotropy);
	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &textureID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const {
		glBindSampler(slot, samplerID);
		glBindTextureUnit(slot, textureID);
	}
}