#pragma once

#ifdef CRISP_PLATFORM_WINDOWS

extern Crisp::Application* Crisp::CreateApplication();

int main(int argc, char** argv) {
	Crisp::Log::Init();

	CRISP_PROFILE_BEGIN_SESSION("Startup", "profiling/CrispProfiler-Startup.json");
	auto app = Crisp::CreateApplication();
	CRISP_PROFILE_END_SESSION();

	CRISP_PROFILE_BEGIN_SESSION("Runtime", "profiling/CrispProfiler-Runtime.json");
	app->Run();
	CRISP_PROFILE_END_SESSION();

	CRISP_PROFILE_BEGIN_SESSION("Shutdown", "profiling/CrispProfiler-Shutdown.json");
	delete app;
	CRISP_PROFILE_END_SESSION();

	return 0;
}

#endif