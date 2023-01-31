#include <Crisp.h>

#include <imgui/imgui.h>

class ExampleLayer : public Crisp::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {
		//CRISP_INFO("ExampleLayer::Update");
		if (Crisp::Input::IsKeyPressed(CRISP_a))
			CRISP_INFO("a pressed");
		if (Crisp::Input::IsMouseButtonDown(CRISP_MOUSE_BUTTON_LEFT))
			CRISP_INFO("left button pressed");
		if (Crisp::Input::IsMouseButtonDown(CRISP_MOUSE_BUTTON_RIGHT))
			CRISP_INFO("right button pressed");
		if (Crisp::Input::IsMouseButtonDown(CRISP_MOUSE_BUTTON_MIDDLE))
			CRISP_INFO("middle button pressed");
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Test Window");
		ImGui::Text("Testing.....");
		ImGui::End();
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