#pragma once
#include <vector>
#include <initializer_list>

namespace Crisp {
	enum class ShaderDataType {
		None = 0,
		Float, 
		Vec2, Vec3, Vec4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::Float:		return 4;
			case ShaderDataType::Vec2:		return 4 * 2;
			case ShaderDataType::Vec3:		return 4 * 3;
			case ShaderDataType::Vec4:		return 4 * 4;
			case ShaderDataType::Mat3:		return 4 * 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4 * 4;
			case ShaderDataType::Int:		return 4;
			case ShaderDataType::Int2:		return 4 * 2;
			case ShaderDataType::Int3:		return 4 * 3;
			case ShaderDataType::Int4:		return 4 * 4;
			case ShaderDataType::Bool:		return 1;
		}

		CRISP_CORE_ASSERT(false, "Unknown shader data type.");
		return 0;
	}

	struct BufferElement {
		ShaderDataType type;
		std::string name;
		uint32_t size;
		uint32_t offset;
		bool normalized;

		BufferElement() : type(ShaderDataType::None), name(""), size(0), offset(0), normalized(false) {}
		BufferElement(ShaderDataType _type, const std::string& _name, bool normalized = false) : type(_type), name(_name), size(ShaderDataTypeSize(_type)), offset(0), normalized(normalized) {}

		uint32_t GetComponentCount() const {
			switch (type) {
			case ShaderDataType::Float:		return 1;
			case ShaderDataType::Vec2:		return 2;
			case ShaderDataType::Vec3:		return 3;
			case ShaderDataType::Vec4:		return 4;
			case ShaderDataType::Mat3:		return 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4;
			case ShaderDataType::Int:		return 1;
			case ShaderDataType::Int2:		return 2;
			case ShaderDataType::Int3:		return 3;
			case ShaderDataType::Int4:		return 4;
			case ShaderDataType::Bool:		return 1;
			}

			CRISP_CORE_ASSERT(false, "Unknown shader data type.");
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements) : elements(elements) {
			CalculateOffsetsAndStride();
		}

		inline uint32_t GetStride() const { return stride; }
		inline const std::vector<BufferElement>& GetElements() const { return elements; }

		std::vector<BufferElement>::iterator begin() { return elements.begin(); }
		std::vector<BufferElement>::iterator end() { return elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return elements.end(); }
	private:
		void CalculateOffsetsAndStride() {
			uint32_t offset = 0;
			stride = 0;
			for (auto& element : elements) {
				element.offset = offset;
				offset += element.size;
				stride += element.size;
			}
		}
	private:
		std::vector<BufferElement> elements;
		uint32_t stride = 0;
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
	};
}