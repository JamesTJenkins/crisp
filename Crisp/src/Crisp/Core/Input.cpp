#include "CrispPCH.h"
#include "Input.h"

namespace Crisp {
    Input* Input::instance = new Input();

    Input::Input() {
        keystate = SDL_GetKeyboardState(NULL);
    };
    
    Input::~Input() {};

    void Input::OnUpdateImpl() {
        keystate = SDL_GetKeyboardState(NULL);

        lastMouseState = mouseState;
        mouseState = SDL_GetMouseState(&x, &y);
        Uint32 result = lastMouseState ^ mouseState;
        mouseDownState = mouseState & result;
        mouseUpState = ~mouseState & result;
        mouseHeldState = mouseState & ~result;

        mouseWheelX = 0;
        mouseWheelY = 0;
    }

    void Input::OnEventImpl(const SDL_Event* e) {
        switch (e->type) {
        case SDL_MOUSEMOTION:
            relativeMouseX = (int)e->motion.xrel;
            relativeMouseY = (int)e->motion.yrel;
            break;
        case SDL_MOUSEWHEEL:
            mouseWheelX = e->wheel.x;
            mouseWheelY = e->wheel.y;
            break;
        }
	}

	bool Input::IsKeyPressedImpl(int keycode) const {
        return keystate[SDL_GetScancodeFromKey(keycode)];
    }

	bool Input::IsMouseButtonDownImpl(int button) const {
        return mouseDownState & SDL_BUTTON(button);
    }

	bool Input::IsMouseButtonHeldImpl(int button) const {
        return mouseHeldState & SDL_BUTTON(button);
    }

	bool Input::IsMouseButtonUpImpl(int button) const {
        return mouseUpState & SDL_BUTTON(button);
    }

	std::pair<int, int> Input::MouseScrollImpl() const {
        return { mouseWheelX, mouseWheelY };
    }

    int Input::GetMouseScrollXImpl() const {
        return mouseWheelX;
    }

    int Input::GetMouseScrollYImpl() const {
        return mouseWheelY;
    }

	std::pair<int, int> Input::GetMousePositionImpl() const {
        return { x, y };
    }

	int Input::GetMouseXImpl() const {
        return x;
    }

	int Input::GetMouseYImpl() const {
        return y;
    }

    std::pair<int, int> Input::GetRelativeMousePositionImpl() const {
        return { relativeMouseX, relativeMouseY };
    }

    int Input::GetRelativeMouseXImpl() const {
        return relativeMouseX;
    }

    int Input::GetRelativeMouseYImpl() const {
        return relativeMouseY;
    }
}