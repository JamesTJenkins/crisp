#pragma once
#include "CrispPCH.h"
#include "Crisp/Core.h"

namespace Crisp {
	struct WindowProperties {
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProperties(const std::string& _title = "Crisp", unsigned int _width = 1280, unsigned int _height = 720) : title(_title), width(_width), height(_height) {}
	};

	// Interface for a desktop window

	class CRISP_API Window {
	public:
		virtual ~Window() {};

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window Attributes
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProperties& properties = WindowProperties());
	};
}