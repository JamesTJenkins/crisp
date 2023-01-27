#include <Crisp.h>

class ExampleLayer : public Crisp::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {
		CRISP_INFO("ExampleLayer::Update");
	}
};

class Game : public Crisp::Application {
public:
	Game() {
		PushLayer(new ExampleLayer());
	}
	~Game() {}
};

Crisp::Application* Crisp::CreateApplication() {
	return new Game();
}