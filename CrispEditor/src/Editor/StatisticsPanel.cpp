#include "StatisticsPanel.h"
#include <imgui/imgui.h>

#include "Crisp.h"

namespace Crisp {
	void StatisticsPanel::OnImGuiRender() {
		ImGui::Begin("Statistics");
		ImGui::Text("Rendering Stats:");
		ImGui::Text("Draw Calls: %d", Renderer::GetStats().DrawCalls);
		ImGui::Text("Quad Count: %d", Renderer::GetStats().QuadCount);
		ImGui::Text("Vertex Count: %d", Renderer::GetStats().GetTotalVertexCount());
		ImGui::Text("Index Count: %d", Renderer::GetStats().GetTotalIndexCount());
		ImGui::End();
	}
}