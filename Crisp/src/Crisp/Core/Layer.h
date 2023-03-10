#pragma once
#include "Crisp/Core/Core.h"
#include <SDL.h>

namespace Crisp {
	class Layer	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(const SDL_Event* e) {}

		inline const std::string& GetName() const { return debugName; }
	protected:
		std::string debugName;
	};
}
