#include "CrispPCH.h"
#include "WindowsWindow.h"

#include <glad/glad.h>

namespace Crisp {
	static bool sdlInitialized = false;

	Window* Window::Create(const WindowProperties& properties) {
		return new WindowsWindow(properties);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties) {
		Initialize(properties);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::OnUpdate() {
		SDL_GL_SwapWindow(window);
	}

	// TODO: add adaptive sync (-1)?
	void WindowsWindow::SetVSync(bool enabled) {
		if (enabled) 
			SDL_GL_SetSwapInterval(1);
		else
			SDL_GL_SetSwapInterval(0);
		data.vSync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return data.vSync;
	}

	void WindowsWindow::Initialize(const WindowProperties& properties) {
		data.title = properties.title;
		data.width = properties.width;
		data.height = properties.height;

		CRISP_CORE_INFO("Creating window {0} ({1}, {2})", properties.title, properties.width, properties.height);

		if (!sdlInitialized) {
			int success = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
			CRISP_CORE_ASSERT(success, "Could not initialize SDL");
			sdlInitialized = true;
		}

		// Initialize openGL
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

		// Create SDL window
		window = SDL_CreateWindow(
			data.title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			data.width,
			data.height,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
		);

		// openGL context creation
		SDL_GLContext context = SDL_GL_CreateContext(window);
		SDL_GL_MakeCurrent(window, context);
		// Set window vsync
		SetVSync(true);
		// Load GLAD
		int status = gladLoadGLLoader(SDL_GL_GetProcAddress);
		CRISP_CORE_ASSERT(status, "Failed to initialize glad");
		// Set viewport
		glViewport(0, 0, properties.width, properties.height);
	}

	void WindowsWindow::Shutdown() {
		SDL_DestroyWindow(window);
	}
}