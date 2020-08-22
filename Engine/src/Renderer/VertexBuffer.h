#pragma once

#include <initializer_list>
#include <vector>
#include <string>

#include "Macro\Assert.h"
#include "Core\Memory.h"

namespace Engine {

	enum class ShaderDataType {
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) 
	{
		switch (type) {
			case ShaderDataType::Float: return sizeof(float);
			case ShaderDataType::Float2: return sizeof(float) * 2;
			case ShaderDataType::Float3: return sizeof(float) * 3;
			case ShaderDataType::Float4: return sizeof(float) * 4;

			case ShaderDataType::Mat3: return sizeof(float) * 3 * 3;
			case ShaderDataType::Mat4: return sizeof(float) * 4 * 4;

			case ShaderDataType::Int: return sizeof(int);
			case ShaderDataType::Int2: return sizeof(int) * 2;
			case ShaderDataType::Int3: return sizeof(int) * 3;
			case ShaderDataType::Int4: return sizeof(int) * 4;

			case ShaderDataType::Bool: return sizeof(bool);
		}

		GE_CORE_ASSERT(false, "Unknown shader data type");
		return 0;
	}

	struct BufferElement 
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		size_t Offset;
		bool Normalized;

		BufferElement() = default;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const 
		{
			switch (Type) {
				case ShaderDataType::Float: return 1;
				case ShaderDataType::Float2: return 2;
				case ShaderDataType::Float3: return 3;
				case ShaderDataType::Float4: return 4;

				case ShaderDataType::Mat3: return 3 * 3;
				case ShaderDataType::Mat4: return 4 * 4;

				case ShaderDataType::Int: return 1;
				case ShaderDataType::Int2: return 2;
				case ShaderDataType::Int3: return 3;
				case ShaderDataType::Int4: return 4;

				case ShaderDataType::Bool: return 1;
			}

			GE_CORE_ASSERT(false, "Unknown shader data type");
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout() : m_Stride(0) {}
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetAndStride();
		};

		inline uint32_t GetStride() const { return m_Stride; };
		inline const std::vector<BufferElement>& GetBufferElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetAndStride()
		{
			size_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(const void* data, uint32_t size) const = 0;

		virtual const BufferLayout& GetBufferLayout() const = 0;
		virtual void SetBufferLayout(const BufferLayout& layout) = 0;
	};

	class VertexBufferFactory {
	public:
		static Ref<VertexBuffer> Create(uint32_t size);
		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
	};

}
