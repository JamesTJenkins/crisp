#pragma once
#include <memory>

#ifdef _WIN32
	#define CRISP_PLATFORM_WINDOWS
#elif defined(__APPLE__) || defined(__MACH__)
	#define CRISP_PLATFORM_MACOS
	#error "MacOS is not supported"
#elif defined(__linux__)
	#define CRISP_PLATFORM_LINUX
	#error "Linux is not supported"
#else
	#error "Unsupported platform"
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