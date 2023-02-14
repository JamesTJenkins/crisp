#pragma once
#include <glm/glm.hpp>

#include "Texture.h"

namespace Crisp {
	class SubTexture2D {
	public:
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);

		const Ref<Texture2D> GetTexture() const { return texture; }
		const glm::vec2* GetTexCoords() const { return texcoords; }

		static Ref<SubTexture2D> CreateFromCoordinates(const Ref<Texture2D>& texture, const glm::vec2& coordinates, const glm::vec2& cellSize, const glm::vec2& spriteSize = { 1, 1 });
	private:
		Ref<Texture2D> texture;

		glm::vec2 texcoords[4];
	};
}