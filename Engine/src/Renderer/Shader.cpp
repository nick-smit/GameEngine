#include "pch.h"
#include "Shader.h"
#include "Platform\Renderer\OpenGL\OpenGLShader.h"
#include "Core\File.h"

namespace Engine {
	
	Ref<Shader> ShaderFactory::FromFile(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
	{
		std::string vertexShader = File::Read(vertexShaderFile);
		std::string fragmentShader = File::Read(fragmentShaderFile);

		return CreateRef<OpenGLShader>(vertexShader, fragmentShader);
	}

	Ref<Shader> ShaderFactory::FromSource(const std::string& vertexShader, const std::string& fragmentShader)
	{
		return CreateRef<OpenGLShader>(vertexShader, fragmentShader);
	}

}