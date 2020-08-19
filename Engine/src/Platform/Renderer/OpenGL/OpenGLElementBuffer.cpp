#include "pch.h"
#include "OpenGLElementBuffer.h"

#include <glad\glad.h>

namespace Engine {
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;
		}

		GE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLElementBuffer::OpenGLElementBuffer()
	{
		glGenVertexArrays(1, &m_VertexArrayId);
	}

	OpenGLElementBuffer::~OpenGLElementBuffer()
	{
		glDeleteVertexArrays(1, &m_VertexArrayId);
	}

	void OpenGLElementBuffer::Bind() const
	{
		glBindVertexArray(m_VertexArrayId);
	}

	void OpenGLElementBuffer::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLElementBuffer::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		GE_CORE_ASSERT(vertexBuffer->GetBufferLayout().GetBufferElements().size(), "Vertex buffer has no layout!");

		glBindVertexArray(m_VertexArrayId);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetBufferLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(
				m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized,
				layout.GetStride(),
				(const void*)element.Offset
			);
			m_VertexBufferIndex++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLElementBuffer::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_VertexArrayId);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}
