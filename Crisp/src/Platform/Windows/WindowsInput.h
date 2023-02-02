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

		virtual bool IsMouseButtonDownImpl(int button) override;
		virtual bool IsMouseButtonHeldImpl(int button) override;
		virtual bool IsMouseButtonUpImpl(int button) override;
		virtual std::pair<int, int> GetMousePositionImpl() override;
		virtual int GetMouseXImpl() override;
		virtual int GetMouseYImpl() override;
	private:
		int x, y;
		const Uint8* keystate;

		Uint32 lastMouseState;
		Uint32 mouseState;
		Uint32 mouseDownState;
		Uint32 mouseUpState;
		Uint32 mouseHeldState;
	};
}
