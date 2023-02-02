#pragma once
#include <sdl.h>

namespace Crisp {
	class CRISP_API Time {
	public:
		Time();
		~Time();

		void OnUpdate();

		inline static double deltaTime;
	private:
		UINT64 now;
		UINT64 last;
	};
}

