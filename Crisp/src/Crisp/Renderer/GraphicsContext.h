#pragma once

namespace Crisp {
	class GraphicsContext {
	public:
		virtual void Initialize() = 0;
		virtual void SwapBuffers() = 0;
	};
}