#pragma once
#include "Crisp/Core.h"
#include <SDL.h>

namespace Crisp {
	class CRISP_API Layer	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}

		inline const std::string& GetName() const { return debugName; }
	protected:
		std::string debugName;
	};
}
