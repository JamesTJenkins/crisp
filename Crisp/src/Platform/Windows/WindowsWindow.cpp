#include "CrispPCH.h"
#include "WindowsWindow.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Crisp {
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
		graphicsContext->SwapBuffers();
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

		// Create SDL window
		window = SDL_CreateWindow(
			data.title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			data.width,
			data.height,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
		);
		// Create graphics context
		graphicsContext = new OpenGLContext(window);
		graphicsContext->Initialize();
		// Set window vsync
		SetVSync(true);
	}

	void WindowsWindow::Shutdown() {
		SDL_DestroyWindow(window);
	}
}