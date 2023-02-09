#include <Crisp.h>
#include <Crisp/Core/EntryPoint.h>
#include "Game2D.h"

class Game : public Crisp::Application {
public:
	Game() {
		PushLayer(new Game2D());
	}
	~Game() {}
};

Crisp::Application* Crisp::CreateApplication() {
	return new Game();
}