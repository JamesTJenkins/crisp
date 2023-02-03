#include "CrispPCH.h"
#include "OpenGLContext.h"

#include <glad/glad.h>

namespace Crisp {
	OpenGLContext::OpenGLContext(SDL_Window* windowHandle) : windowHandle(windowHandle) {
		CRISP_CORE_ASSERT(windowHandle, "Window was not created!")
	}

	void OpenGLContext::Initialize() {
		// openGL context creation
		SDL_GLContext context = SDL_GL_CreateContext(windowHandle);
		SDL_GL_MakeCurrent(windowHandle, context);
		// Load GLAD
		int status = gladLoadGLLoader(SDL_GL_GetProcAddress);
		CRISP_CORE_ASSERT(status, "Failed to initialize glad");
		// Set viewport size
		int w, h;
		SDL_GetWindowSize(windowHandle, &w, &h);
		glViewport(0, 0,  w, h);

		CRISP_CORE_INFO("OpenGL Vendor: {0}", glGetString(GL_VENDOR));
		CRISP_CORE_INFO("OpenGL Renderer: {0}", glGetString(GL_RENDERER));
		CRISP_CORE_INFO("OpenGL Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		SDL_GL_SwapWindow(windowHandle);
	}
}