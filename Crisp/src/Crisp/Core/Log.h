#pragma once
#include "Crisp/Core/Core.h"

// ingore warnings in external headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Crisp {
	class Log {
	public:
		static void Init();

		// Core logger is for Crisp engine
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; }
		// Client logger is for an application
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
	};
}

// TODO: Add log stripping

// Crisp Logging
#define CRISP_CORE_TRACE(...)		::Crisp::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CRISP_CORE_INFO(...)		::Crisp::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CRISP_CORE_WARN(...)		::Crisp::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CRISP_CORE_ERROR(...)		::Crisp::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CRISP_CORE_CRITICAL(...)	::Crisp::Log::GetCoreLogger()->critical(__VA_ARGS__)
// App Logging
#define CRISP_TRACE(...)			::Crisp::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CRISP_INFO(...)				::Crisp::Log::GetClientLogger()->info(__VA_ARGS__)
#define CRISP_WARN(...)				::Crisp::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CRISP_ERROR(...)			::Crisp::Log::GetClientLogger()->error(__VA_ARGS__)
#define CRISP_CRITICAL(...)			::Crisp::Log::GetClientLogger()->critical(__VA_ARGS__)