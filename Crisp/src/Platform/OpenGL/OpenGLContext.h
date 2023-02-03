#pragma once
#include "Crisp/Renderer/GraphicsContext.h"

#include <SDL.h>

namespace Crisp {
	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(SDL_Window* windowHandle);

		virtual void Initialize() override;
		virtual void SwapBuffers() override;
	private:
		SDL_Window* windowHandle;
	};
}

