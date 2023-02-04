#pragma once
#include <memory>

#ifdef CRISP_PLATFORM_WINDOWS
	#if CRISP_DYNAMIC_LINK
		#ifdef CRISP_BUILD_DLL
			#define CRISP_API __declspec(dllexport)
		#else
			#define CRISP_API __declspec(dllimport)
		#endif
	#else
		#define CRISP_API
	#endif
#else
	#error Crisp only support windows
#endif

#ifndef CRISP_DEBUG
	#define CRISP_ENABLE_ASSERTS
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

namespace Crisp {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}