#pragma once
#include "CrispPCH.h"

#include "Crisp/Core.h"
#include "Crisp/Events/Event.h"

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
		using EventCallbackFunction = std::function<void(Event&)>;

		virtual ~Window() {};

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window Attributes
		virtual void SetEventCallback(const EventCallbackFunction& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProperties& properties = WindowProperties());
	};
}