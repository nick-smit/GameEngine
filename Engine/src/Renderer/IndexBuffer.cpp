#include "pch.h"
#include "IndexBuffer.h"

#include "Platform\Renderer\OpenGL\OpenGLIndexBuffer.h"

namespace Engine {


	Ref<IndexBuffer> IndexBufferFactory::Create(uint32_t* indices, uint32_t count)
	{
		return CreateRef<OpenGLIndexBuffer>(indices, count);
	}
}
