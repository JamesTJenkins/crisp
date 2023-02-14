#include "CrispPCH.h"
#include "Crisp/Renderer/SubTexture.h"

namespace Crisp {
	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max) : texture(texture) {
		texcoords[0] = { min.x, min.y };
		texcoords[1] = { max.x, min.y };
		texcoords[2] = { max.x, max.y };
		texcoords[3] = { min.x, max.y };
	}

	Ref<SubTexture2D> SubTexture2D::CreateFromCoordinates(const Ref<Texture2D>& texture, const glm::vec2& coordinates, const glm::vec2& cellSize, const glm::vec2& spriteSize) {
		glm::vec2 min = { (coordinates.x * cellSize.x) / texture->GetWidth(), (coordinates.y * cellSize.y) / texture->GetHeight() };
		glm::vec2 max = { ((coordinates.x + spriteSize.x) * cellSize.x) / texture->GetWidth(), ((coordinates.y + spriteSize.y) * cellSize.y) / texture->GetHeight() };

		return CreateRef<SubTexture2D>(texture, min, max);
	}
}