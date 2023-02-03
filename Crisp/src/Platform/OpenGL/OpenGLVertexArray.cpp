#include "CrispPCH.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Crisp {
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type) {
		case Crisp::ShaderDataType::Vec2:	return GL_FLOAT;
		case Crisp::ShaderDataType::Vec3:	return GL_FLOAT;
		case Crisp::ShaderDataType::Vec4:	return GL_FLOAT;
		case Crisp::ShaderDataType::Mat3:	return GL_FLOAT;
		case Crisp::ShaderDataType::Mat4:	return GL_FLOAT;
		case Crisp::ShaderDataType::Int:	return GL_INT;
		case Crisp::ShaderDataType::Int2:	return GL_INT;
		case Crisp::ShaderDataType::Int3:	return GL_INT;
		case Crisp::ShaderDataType::Int4:	return GL_INT;
		case Crisp::ShaderDataType::Bool:	return GL_BOOL;
		}

		CRISP_CORE_ASSERT(false, "Unknown shader data type.");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &rendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &rendererID);
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(rendererID);
	}

	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
		Bind();
		vertexBuffer->Bind();

		CRISP_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout.");

		uint32_t index = 0;
		for (const auto& element : vertexBuffer->GetLayout()) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				(const void*)element.offset
			);
			index++;
		}

		vertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& _indexBuffer) {
		Bind();
		_indexBuffer->Bind();

		indexBuffer = _indexBuffer;
	}
}