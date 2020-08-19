#include "pch.h"
#include "OpenGLIndexBuffer.h"

#include <glad\glad.h>

namespace Engine {

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		glGenBuffers(1, &m_IndexBufferId);

		// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
		// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 
		glBindBuffer(GL_ARRAY_BUFFER, m_IndexBufferId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uint32_t) * count, indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_IndexBufferId);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferId);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}
