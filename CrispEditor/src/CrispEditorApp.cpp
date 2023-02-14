#include <Crisp.h>
#include <Crisp/Core/EntryPoint.h>
#include "EditorLayer.h"

namespace Crisp {
	class CrispEditor : public Application {
	public:
		CrispEditor() : Application("Crisp Editor") {
			PushLayer(new EditorLayer());
		}
		~CrispEditor() {}
	};

	Application* CreateApplication() {
		return new CrispEditor();
	}
}