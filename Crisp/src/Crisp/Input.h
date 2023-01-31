#pragma once
#include "Crisp/Core.h"

namespace Crisp {
	class CRISP_API Input {
	public:
		inline static void OnUpdate() { instance->OnUpdateImpl(); }

		inline static bool IsKeyPressed(int keycode) { return instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonDown(int button) { return instance->IsMouseButtonDownImpl(button); }
		inline static bool IsMouseButtonHeld(int button) { return instance->IsMouseButtonHeldImpl(button); }
		inline static bool IsMouseButtonUp(int button) { return instance->IsMouseButtonUpImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return instance->GetMousePositionImpl(); }
		inline static bool GetMouseX() { return instance->GetMouseXImpl(); }
		inline static bool GetMouseY() { return instance->GetMouseYImpl(); }
	protected:
		inline virtual void OnUpdateImpl() = 0;
		inline virtual bool IsKeyPressedImpl(int keycode) = 0;
		inline virtual bool IsMouseButtonDownImpl(int button) = 0;
		inline virtual bool IsMouseButtonHeldImpl(int button) = 0;
		inline virtual bool IsMouseButtonUpImpl(int button) = 0;
		inline virtual std::pair<float, float> GetMousePositionImpl() = 0;
		inline virtual float GetMouseXImpl() = 0;
		inline virtual float GetMouseYImpl() = 0;
	private:
		static Input* instance;
	};
}