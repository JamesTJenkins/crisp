#include "CrispPCH.h"
#include "WindowsWindow.h"

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
	}

	// TODO: add adaptive sync (-1)?
	// TODO: if adding vulkan fix this
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

		if (sdlInitialized) {
			int success = SDL_Init(SDL_INIT_VIDEO);
			CRISP_CORE_ASSERT(success, "Could not initialize SDL");
		}

		window = SDL_CreateWindow(
			data.title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			data.width,
			data.height,
			0
		);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown() {
		SDL_DestroyWindow(window);
	}
}