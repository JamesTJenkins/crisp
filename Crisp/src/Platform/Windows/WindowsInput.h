#pragma once
#include "Crisp/Input.h"

#include <SDL_stdinc.h>

namespace Crisp {
	class WindowsInput : public Input {
	public:
		WindowsInput();
		~WindowsInput();
	protected:
		virtual void OnUpdateImpl() override;

		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	private:
		const Uint8* keystate;
		Uint32 mouseState;
		Uint32 lastMouseState;
		int x, y;
	};
}
