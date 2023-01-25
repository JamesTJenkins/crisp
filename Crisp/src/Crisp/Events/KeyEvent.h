#pragma once
#include "Event.h"

#include <sstream>

namespace Crisp {
	class CRISP_API KeyEvent : public Event {
	public:
		inline int GetKeyCode() const { return keycode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int _keycode) : keycode(_keycode) {}

		int keycode;
	};

	class CRISP_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keycode, int _repeatCount) : KeyEvent(keycode), repeatCount(_repeatCount) {}
	
		inline int GetRepeatCount() const { return repeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << keycode << " (" << repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int repeatCount;
	};

	class CRISP_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}