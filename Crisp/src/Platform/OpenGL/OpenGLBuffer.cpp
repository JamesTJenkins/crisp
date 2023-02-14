#include "CrispPCH.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Crisp {

	// VERTEX

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) {
		CRISP_PROFILE_FUNCTION();

		glCreateBuffers(1, &rendererID);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
		CRISP_PROFILE_FUNCTION();

		glCreateBuffers(1, &rendererID);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		CRISP_PROFILE_FUNCTION();

		glDeleteBuffers(1, &rendererID);
	}

	void OpenGLVertexBuffer::Bind() const {
		CRISP_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	}

	void OpenGLVertexBuffer::Unbind() const {
		CRISP_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size) {
		Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	// INDEX

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : count(count) {
		CRISP_PROFILE_FUNCTION();

		glCreateBuffers(1, &rendererID);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		CRISP_PROFILE_FUNCTION();

		glDeleteBuffers(1, &rendererID);
	}

	void OpenGLIndexBuffer::Bind() const {
		CRISP_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
	}

	void OpenGLIndexBuffer::Unbind() const {
		CRISP_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}