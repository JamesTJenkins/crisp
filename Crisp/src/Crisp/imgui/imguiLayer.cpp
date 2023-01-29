#include "CrispPCH.h"
#include "imguiLayer.h"

#include "Crisp/Time.h"
#include "Crisp/Application.h"
#include "Platform/OpenGL/imguiOpenGLRenderer.h"
#include "Platform/SDL/imguiSDLRenderer.h"

namespace Crisp {
	imguiLayer::imguiLayer() : Layer("imguiLayer") {

	}

	imguiLayer::~imguiLayer() {

	}

	void imguiLayer::OnAttach() {
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// Setup Platform/Renderer backends (May need to change from current windows and context in future with multiple windows)
		ImGui_ImplSDL2_InitForOpenGL(SDL_GL_GetCurrentWindow(), SDL_GL_GetCurrentContext());
		ImGui_ImplOpenGL3_Init("#version 460");

		// Fonts
		io.Fonts->AddFontDefault();
	}

	void imguiLayer::OnDetach() {

	}

	void imguiLayer::OnUpdate() {
		ImGuiIO& io = ImGui::GetIO();
		Application& application = Application::Get();
		io.DisplaySize = ImVec2(application.GetWindow().GetWidth(), application.GetWindow().GetHeight());
		io.DeltaTime = Time::deltaTime;

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		// TESTING
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
		// TESTING

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// SDL_GL_SwapWindow(window); <-- This is done by the windows OnUpdate()
	}

	void imguiLayer::OnEvent(const SDL_Event* e) {
		ImGui_ImplSDL2_ProcessEvent(e);
	}
}