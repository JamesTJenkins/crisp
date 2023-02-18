#pragma once
#include "Crisp.h"

namespace Crisp {
	class Test : public ScriptableEntity {
	public:
		void OnCreate() {
			CRISP_CORE_INFO("Test OnCreate called.");
		}

		void OnDestroy() {
			CRISP_CORE_INFO("Test OnDestroy called.");
		}

		void OnUpdate() {
			CRISP_CORE_INFO("Test OnUpdate called.");
		}
	};
}