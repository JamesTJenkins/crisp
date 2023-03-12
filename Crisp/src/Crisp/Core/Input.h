#pragma once
#include "Crisp/Core/Core.h"
#include <SDL.h>

namespace Crisp {
	class Input {
	public:
		inline static void OnUpdate() { instance->OnUpdateImpl(); }
		inline static void OnEvent(const SDL_Event* e) { instance->OnEventImpl(e); }

		inline static bool IsKeyPressed(int keycode) { return instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonDown(int button) { return instance->IsMouseButtonDownImpl(button); }
		inline static bool IsMouseButtonHeld(int button) { return instance->IsMouseButtonHeldImpl(button); }
		inline static bool IsMouseButtonUp(int button) { return instance->IsMouseButtonUpImpl(button); }
		inline static std::pair<int, int> MouseScroll() { return instance->MouseScrollImpl(); }
		inline static int GetMouseScrollX() { return instance->GetMouseScrollXImpl(); }
		inline static int GetMouseScrollY() { return instance->GetMouseScrollYImpl(); }
		inline static std::pair<int, int> GetMousePosition() { return instance->GetMousePositionImpl(); }
		inline static int GetMouseX() { return instance->GetMouseXImpl(); }
		inline static int GetMouseY() { return instance->GetMouseYImpl(); }
		inline static std::pair<int, int> GetRelativeMousePosition() { return instance->GetRelativeMousePositionImpl(); }
		inline static int GetRelativeMouseX() { return instance->GetRelativeMouseXImpl(); }
		inline static int GetRelativeMouseY() { return instance->GetRelativeMouseYImpl(); }
	private:
		Input();
		~Input();

		void OnUpdateImpl();
		void OnEventImpl(const SDL_Event* e);
		bool IsKeyPressedImpl(int keycode) const;
		bool IsMouseButtonDownImpl(int button) const;
		bool IsMouseButtonHeldImpl(int button) const;
		bool IsMouseButtonUpImpl(int button) const;
		std::pair<int, int> MouseScrollImpl() const;
		int GetMouseScrollXImpl() const;
		int GetMouseScrollYImpl() const;
		std::pair<int, int> GetMousePositionImpl() const;
		int GetMouseXImpl() const;
		int GetMouseYImpl() const;
		std::pair<int, int> GetRelativeMousePositionImpl() const;
		int GetRelativeMouseXImpl() const;
		int GetRelativeMouseYImpl() const;
	private:
		static Input* instance;
	private:
		const Uint8* keystate;
		
		int x, y;
		int relativeMouseX, relativeMouseY;
		int mouseWheelX, mouseWheelY;

		Uint32 lastMouseState, mouseState, mouseDownState, mouseUpState, mouseHeldState;
	};
}