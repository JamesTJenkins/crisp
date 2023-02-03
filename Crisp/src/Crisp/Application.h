#pragma once
#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "imgui/ImGuiLayer.h"

// TESTING
#include "Crisp/Renderer/Shader.h"
#include "Crisp/Renderer/VertexArray.h"
#include "Crisp/Components/Camera.h"
// TESTING

namespace Crisp {
	class CRISP_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *instance; }

		inline Window& GetWindow() { return *window; }
	private:
		std::unique_ptr<Window> window;
		ImGuiLayer* imguiLayer;
		bool running = true;
		LayerStack layerStack;

		// TESTING
		std::shared_ptr<Shader> shader;
		std::shared_ptr<VertexArray> vertexArray;
		Transform camTransform;
		Camera cam;
		// TESTING
	private:
		static Application* instance;
	};

	// Defined in Crisp application
	Application* CreateApplication();
}
