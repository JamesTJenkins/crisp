#pragma once
#include "Event.h"

namespace Crisp {
	class CRISP_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y) : movedX(x), movedY(y) {}

		inline float GetX() const { return mouseX; }
		inline float GetX() const { return mouseY; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << mouseX << ", " << mouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float mouseX, mouseY;
	};

	class CRISP_API MouseScrolledEvent : public Event {
		MouseScrolledEvent(float _xOffset, _yOffset) : xOffset(_xOffset), yOffset(_yOffset) {}

		inline float GetXOffset() const { return xOffset; }
		inline float GetYOffset() const { return yOffset; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float xOffset, yOffset;
	};

	class CRISP_API MouseButtonEvent : public Event {
	public:
		inline int GetMouseButton() const { return button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int _button) : button(_button) {}

		int button;
	};

	class CRISP_API MouseButtonPressedEvent : public Event {
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class CRISP_API MouseButtonReleasedEvent : public Event {
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}
		
		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << button;
			return ss;
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}