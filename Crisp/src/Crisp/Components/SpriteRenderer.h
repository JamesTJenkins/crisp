#pragma once
#include "Crisp/Core/glm_common.h"

namespace Crisp {
	class SpriteRenderer {
	public:
		SpriteRenderer(const glm::vec4& color = { 1,1,1,1 }) : color(color) {}
	public:
		glm::vec4 color;
	};
}