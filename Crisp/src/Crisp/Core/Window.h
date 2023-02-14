#pragma once
#include "CrispPCH.h"
#include "Crisp/Core/Core.h"

namespace Crisp {
	struct WindowProperties {
		std::string title;
		uint32_t width, height;

		WindowProperties(const std::string& _title = "Crisp App", uint32_t _width = 1280, uint32_t _height = 720) : title(_title), width(_width), height(_height) {}
	};

	// Interface for a desktop window

	class Window {
	public:
		virtual ~Window() {};

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window Attributes
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProperties& properties = WindowProperties());
	};
}