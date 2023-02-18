#pragma once

// USED BY CRISP APPLICATIONS

// BASE
#include "Crisp/Core/Application.h"
#include "Crisp/Core/Log.h"
#include "Crisp/Core/Time.h"
#include "Crisp/Core/Random.h"
#include "Crisp/Scene/Scene.h"

// LAYERS
#include "Crisp/Core/Layer.h"
#include "Crisp/imgui/imguiLayer.h"

// INPUT
#include "Crisp/Core/Keycodes.h"
#include "Crisp/Core/MouseButtonCodes.h"
#include "Crisp/Core/Input.h"

// RENDERING
#include "Crisp/Renderer/Buffer.h"
#include "Crisp/Renderer/RenderCommand.h"
#include "Crisp/Renderer/Renderer.h"
#include "Crisp/Renderer/Shader.h"
#include "Crisp/Renderer/FrameBuffer.h"
#include "Crisp/Renderer/Texture.h"
#include "Crisp/Renderer/VertexArray.h"

// Scene
#include "Crisp/Scene/Entity.h"
#include "Crisp/Scene/SceneCamera.h"
#include "Crisp/Components/EntityProperties.h"
#include "Crisp/Components/ScriptableObject.h"
#include "Crisp/Components/Transform.h"
#include "Crisp/Components/Camera.h"
#include "Crisp/Components/SpriteRenderer.h"