#include "CrispPCH.h"
#include "WindowsInput.h"

#include <SDL.h>

namespace Crisp {
	Input* Input::instance = new WindowsInput();

	WindowsInput::WindowsInput() : keystate(0), mouseState(0), lastMouseState(0), x(0), y(0) {}

	WindowsInput::~WindowsInput() {}

	void WindowsInput::OnUpdateImpl() {
		lastMouseState = mouseState;
		keystate = SDL_GetKeyboardState(NULL);
		mouseState = SDL_GetRelativeMouseState(&x, &y);
	}

	bool WindowsInput::IsKeyPressedImpl(int keycode) {
		return keystate[SDL_GetScancodeFromKey(keycode)];
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button) {
		Uint32 result = lastMouseState ^ mouseState;
		return result & SDL_BUTTON(button);
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