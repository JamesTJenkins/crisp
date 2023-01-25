#include <Crisp.h>

class Game : public Crisp::Application {
public:
	Game() {}
	~Game() {}
};

Crisp::Application* Crisp::CreateApplication() {
	return new Game();
}