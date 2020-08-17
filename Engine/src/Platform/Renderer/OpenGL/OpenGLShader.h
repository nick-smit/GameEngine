#pragma once

#include "Renderer\Shader.h"
#include "glad\glad.h"

namespace Engine {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexShader, const std::string& fragmentShader);
		~OpenGLShader();

		virtual void Bind() override;
		virtual void Unbind() override;
	private:
		uint32_t CompileShader(const std::string& shader, GLenum type);

	private:
		uint32_t m_ShaderProgram;
	};

}