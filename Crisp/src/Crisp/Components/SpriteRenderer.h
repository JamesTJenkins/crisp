#pragma once
#include <glm/glm.hpp>

namespace Crisp {
	class SpriteRenderer {
	public:
		SpriteRenderer(const glm::vec4& color = { 1,1,1,1 }) : color(color) {}

		glm::vec4 color;
	};
}