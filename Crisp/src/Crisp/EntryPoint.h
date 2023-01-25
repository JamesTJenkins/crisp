#pragma once

#ifdef CRISP_PLATFORM_WINDOWS

extern Crisp::Application* Crisp::CreateApplication();

int main(int argc, char** argv) {
	// LOGGER TESTING
	Crisp::Log::Init();
	CRISP_CORE_WARN("Init Core Logging");
	int a = 5;
	CRISP_APP_WARN("Test var={0}", a);
	// LOGGER TESTING

	auto app = Crisp::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif