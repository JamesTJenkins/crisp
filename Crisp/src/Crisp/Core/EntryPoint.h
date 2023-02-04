#pragma once

#ifdef CRISP_PLATFORM_WINDOWS

extern Crisp::Application* Crisp::CreateApplication();

int main(int argc, char** argv) {
	Crisp::Log::Init();
	auto app = Crisp::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif