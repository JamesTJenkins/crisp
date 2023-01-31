#include "CrispPCH.h"
#include "WindowsInput.h"

#include <SDL.h>

// TODO: Add mouse up, mouse held

namespace Crisp {
	Input* Input::instance = new WindowsInput();

	WindowsInput::WindowsInput() : keystate(0), mouseState(0), lastMouseState(0), x(0), y(0) {}

	WindowsInput::~WindowsInput() {}

	void WindowsInput::OnUpdateImpl() {
		keystate = SDL_GetKeyboardState(NULL);
		
		lastMouseState = mouseState;
		mouseState = SDL_GetRelativeMouseState(&x, &y);
		Uint32 result = lastMouseState ^ mouseState;
		mouseDownState = mouseState & result;
		mouseUpState = mouseState & ~result;
		mouseHeldState = ~mouseState & result;
	}

	bool WindowsInput::IsKeyPressedImpl(int keycode) {
		return keystate[SDL_GetScancodeFromKey(keycode)];
	}

	bool WindowsInput::IsMouseButtonDownImpl(int button) {
		return mouseDownState & SDL_BUTTON(button);
	}

	bool WindowsInput::IsMouseButtonHeldImpl(int button) {
		return mouseHeldState & SDL_BUTTON(button);
	}

	bool WindowsInput::IsMouseButtonUpImpl(int button) {
		return mouseUpState & SDL_BUTTON(button);
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl() {
		return { (float)x , (float)y };
	}

	float WindowsInput::GetMouseXImpl() {
		return x;
	}

	float WindowsInput::GetMouseYImpl() {
		return y;
	}
}