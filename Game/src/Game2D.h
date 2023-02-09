#pragma once
#include "Crisp.h"
#include <SDL.h>

class Game2D : public Crisp::Layer {
public:
	Game2D();
	virtual ~Game2D() override;

	Game2D(const Game2D& other) = delete;				// Copy construct
	Game2D& operator=(const Game2D& other) = delete;	// Copy assign

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate() override;
	virtual void OnImGuiRender() override;

	virtual void OnEvent(const SDL_Event* e) override;
private:
	Crisp::Ref<Crisp::VertexArray> vertexArray;
	Crisp::Ref<Crisp::Shader> colorShader;
	Crisp::Ref<Crisp::Texture2D> texture;
	glm::vec4 color;

	Crisp::Transform camTransform;
	Crisp::Transform quadTransform;
	Crisp::Transform quad1Transform;
	Crisp::Camera* cam;
};

