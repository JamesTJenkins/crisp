#include "CrispPCH.h"
#include "Platform/OpenGL/OpenGLRenderAPI.h"

#include <SDL.h>
#include <glad/glad.h>

namespace Crisp {
	static const char* GLDebugTypeToString(GLenum type) {
		switch (type) {
		case GL_DEBUG_TYPE_ERROR: return "GL_DEBUG_TYPE_ERROR";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
		case GL_DEBUG_TYPE_PORTABILITY: return "GL_DEBUG_TYPE_PORTABILITY";
		case GL_DEBUG_TYPE_PERFORMANCE: return "GL_DEBUG_TYPE_PERFORMANCE";
		case GL_DEBUG_TYPE_MARKER: return "GL_DEBUG_TYPE_MARKER";
		case GL_DEBUG_TYPE_PUSH_GROUP: return "GL_DEBUG_TYPE_PUSH_GROUP";
		case GL_DEBUG_TYPE_POP_GROUP: return "GL_DEBUG_TYPE_POP_GROUP";
		case GL_DEBUG_TYPE_OTHER: return "GL_DEBUG_TYPE_OTHER";
		}

		return "Unknown GL error type.";
	}

	static const char* GLDebugSourceToString(GLenum source) {
		switch (source) {
		case GL_DEBUG_SOURCE_API: return "GL_DEBUG_SOURCE_API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "GL_DEBUG_SOURCE_WINDOW_SYSTEM_";
		case GL_DEBUG_SOURCE_SHADER_COMPILER: return "GL_DEBUG_SOURCE_SHADER_COMPILER";
		case GL_DEBUG_SOURCE_THIRD_PARTY: return "GL_DEBUG_SOURCE_THIRD_PARTY";
		case GL_DEBUG_SOURCE_APPLICATION: return "GL_DEBUG_SOURCE_APPLICATION";
		case GL_DEBUG_SOURCE_OTHER: return "GL_DEBUG_SOURCE_OTHER";
		}

		return "Unknown GL source.";
	}

	static void Debug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
		switch (severity) {
		case GL_DEBUG_SEVERITY_LOW:
			CRISP_CORE_WARN("[{0}] {1} ({2}): {3}", GLDebugTypeToString(type), GLDebugSourceToString(source), id, message);
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			CRISP_CORE_ERROR("[{0}] {1} ({2}): {3}", GLDebugTypeToString(type), GLDebugSourceToString(source), id, message);
			break;
		case GL_DEBUG_SEVERITY_HIGH:
			CRISP_CORE_CRITICAL("[{0}] {1} ({2}): {3}", GLDebugTypeToString(type), GLDebugSourceToString(source), id, message);
			break;
		}
	}

	void OpenGLRendererAPI::Initialize() {
		int success = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
		CRISP_CORE_ASSERT(success, "Could not initialize SDL");

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(&Debug, nullptr);
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) {
		glClearColor(color.a, color.b, color.g, color.a);
	}

	void OpenGLRendererAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray) {
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}