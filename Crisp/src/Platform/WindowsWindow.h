#pragma once
#include "Crisp/Window.h"

#include <SDL.h>

namespace Crisp {
	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProperties& properties);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return data.width; }
		inline unsigned int GetHeight() const override { return data.height; }
	
		// Window attributes
		inline void SetEventCallback(const EventCallbackFunction& callback) override { data.eventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
	private:
		virtual void Initialize(const WindowProperties& properties);
		virtual void Shutdown();
	private:
		SDL_Window* window;

		struct WindowData {
			std::string title;
			unsigned int width, height;
			bool vSync;

			EventCallbackFunction eventCallback;
		};

		WindowData data;
	};
}
