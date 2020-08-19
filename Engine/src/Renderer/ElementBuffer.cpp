#include "pch.h"
#include "ElementBuffer.h"

#include "Platform\Renderer\OpenGL\OpenGLElementBuffer.h"

namespace Engine {

	Ref<ElementBuffer> ElementBufferFactory::Create()
	{
		return CreateRef<OpenGLElementBuffer>();
	}

}
