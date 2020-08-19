#include "pch.h"
#include "VertexBuffer.h"

#include "Platform\Renderer\OpenGL\OpenGLVertexBuffer.h"

namespace Engine {

	Ref<VertexBuffer> VertexBufferFactory::Create(float* vertices, uint32_t size)
	{
		return CreateRef<OpenGLVertexBuffer>(vertices, size);
	}

}
