#pragma once

#ifdef CRISP_PLATFORM_WINDOWS
	#ifdef CRISP_BUILD_DLL
		#define CRISP_API __declspec(dllexport)
	#else
		#define CRISP_API __declspec(dllimport)
	#endif
#else
	#error Crisp only support windows
#endif

#ifdef CRISP_ENABLE_ASSERTS
	#define CRISP_ASSERT(x, ...) { if(!(x)) { CRISP_ERROR("Assertion Failed: {0}", __VA__ARGS__); __debugbreak(); } }
	#define CRISP_CORE_ASSERT(x, ...) { if(!(x)) { CRISP_CORE_ERROR("Assertion Failed: {0}", __VA__ARGS__); __debugbreak(); } }
#else
	#define CRISP_ASSERT(x, ...)
	#define CRISP_CORE_ASSERT(x, ...)
#endif

// Bitfields
#define BIT(x) (1 << x)

#include "Crisp/Log.h"