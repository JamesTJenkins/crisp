#pragma once
#include "Crisp/Core.h"

namespace Crisp {
	// Events are currently blocking, upon an event occuring it gets dispatched and dealt with immediately
	// TODO: Add event buffer and process events upon an update call

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput		 = BIT(1),
		EventCategoryKeyboard	 = BIT(2),
		EventCategoryMouse		 = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class CRISP_API Event {
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	protected:
		bool handled = false;
	};

	class EventDispatcher {
		template<typename Type>
		using EventFunction = std::function<bool(Type&)>;
	public:
		EventDispatcher(Event& e) : _event(e) {}

		template<typename Type>
		bool Dispatch(EventFunction<Type> function) {
			if (_event.GetEventType() == Type::GetStaticType()) {
				_event.handled = function(*(Type*)&_event);
				return true;
			}
		}
	private:
		Event& _event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}
}