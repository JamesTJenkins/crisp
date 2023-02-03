#include "CrispPCH.h"
#include "Crisp/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace Crisp {
	RendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI();
}