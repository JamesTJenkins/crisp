#include <Crisp.h>

class ExampleLayer : public Crisp::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {
		//CRISP_INFO("ExampleLayer::Update");
		if (Crisp::Input::IsKeyPressed(CRISP_a))
			CRISP_INFO("a pressed");
		if (Crisp::Input::IsMouseButtonPressed(CRISP_MOUSE_BUTTON_LEFT))
			CRISP_INFO("left button pressed");
		if (Crisp::Input::IsMouseButtonPressed(CRISP_MOUSE_BUTTON_RIGHT))
			CRISP_INFO("right button pressed");
		if (Crisp::Input::IsMouseButtonPressed(CRISP_MOUSE_BUTTON_MIDDLE))
			CRISP_INFO("middle button pressed");
	}
};

class Game : public Crisp::Application {
public:
	Game() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Crisp::imguiLayer());
	}
	~Game() {}
};

Crisp::Application* Crisp::CreateApplication() {
	return new Game();
}