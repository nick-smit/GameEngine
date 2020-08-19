#include "pch.h"
#include "RenderCommand.h"

#include "Platform\Renderer\OpenGL\OpenGLRendererAPI.h"

namespace Engine {
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

	Scope<RendererAPI> RendererAPI::Create()
	{
		return CreateScope<OpenGLRendererAPI>();
	}
}
