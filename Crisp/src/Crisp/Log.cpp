#include "CrispPCH.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Crisp {
	std::shared_ptr<spdlog::logger> Log::coreLogger;
	std::shared_ptr<spdlog::logger> Log::clientLogger;

	void Log::Init() {
		// Set formatting go to spdlog wiki if want to change
		spdlog::set_pattern("%^[%T] %n: %v%$");
		coreLogger = spdlog::stdout_color_mt("Crisp");
		coreLogger->set_level(spdlog::level::trace);

		clientLogger = spdlog::stdout_color_mt("App");
		clientLogger->set_level(spdlog::level::trace);
	}
}