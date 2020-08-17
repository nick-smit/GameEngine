#include "pch.h"
#include "Shader.h"
#include "Platform\Renderer\OpenGL\OpenGLShader.h"

namespace Engine {
	
	Ref<Shader> ShaderFactory::FromFile(const std::string& filename)
	{
		GE_ASSERT(false, "ShaderFactory::FromFile is not yet available.");
		return CreateRef<OpenGLShader>("", "");
	}

	Ref<Shader> ShaderFactory::FromSource(const std::string& vertexShader, const std::string& fragmentShader)
	{
		return CreateRef<OpenGLShader>(vertexShader, fragmentShader);
	}

}