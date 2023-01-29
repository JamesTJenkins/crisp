#include "CrispPCH.h"
#include "Time.h"

namespace Crisp {
	Time::Time() {
		now = SDL_GetPerformanceCounter();
		last = 0;
		deltaTime = 0;
	}

	Time::~Time() {
	}

	void Time::OnUpdate() {
		last = now;
		now = SDL_GetPerformanceCounter();

		deltaTime = (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());
	}
}
