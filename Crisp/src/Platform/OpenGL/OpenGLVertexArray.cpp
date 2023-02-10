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
		CRISP_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &rendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		CRISP_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &rendererID);
	}

	void OpenGLVertexArray::Bind() const {
		CRISP_PROFILE_FUNCTION();

		glBindVertexArray(rendererID);
	}

	void OpenGLVertexArray::Unbind() const {
		CRISP_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
		CRISP_PROFILE_FUNCTION();

		CRISP_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout.");

		Bind();
		vertexBuffer->Bind();

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

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& _indexBuffer) {
		CRISP_PROFILE_FUNCTION();
		
		Bind();
		_indexBuffer->Bind();

		indexBuffer = _indexBuffer;
	}
}