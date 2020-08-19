#pragma once

#include "Renderer\VertexBuffer.h"

namespace Engine {

	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		
		virtual const BufferLayout& GetBufferLayout() const override { return m_BufferLayout; };
		virtual void SetBufferLayout(const BufferLayout& layout) override { m_BufferLayout = layout; };

	private:
		uint32_t m_VertexBufferId;
		BufferLayout m_BufferLayout;
	};

}
