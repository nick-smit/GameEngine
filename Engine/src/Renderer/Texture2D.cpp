#include "pch.h"
#include "Texture2D.h"

#include "Platform\Renderer\OpenGL\OpenGLTexture2D.h"

namespace Engine {

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		return CreateRef<OpenGLTexture2D>(width, height);
	}

	Ref<Texture2D> Texture2D::FromFile(const std::string& file)
	{
		return CreateRef<OpenGLTexture2D>(file);
	}

}
