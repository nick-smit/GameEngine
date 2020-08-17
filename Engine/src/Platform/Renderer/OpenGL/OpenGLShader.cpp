#include "pch.h"
#include "OpenGLShader.h"

namespace Engine {
	OpenGLShader::OpenGLShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		uint32_t vertexShaderId = CompileShader(vertexShader, GL_VERTEX_SHADER);
		uint32_t fragmentShaderId = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

		m_ShaderProgram = glCreateProgram();
		glAttachShader(m_ShaderProgram, vertexShaderId);
		glAttachShader(m_ShaderProgram, fragmentShaderId);
		glLinkProgram(m_ShaderProgram);

		{
			int success;
			glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);

			if (!success) {
				char info[512];
				glGetProgramInfoLog(m_ShaderProgram, 512, NULL, info);
				LOG_CORE_ERROR(info)
			}

			GE_ASSERT(success, "Failed to link program");
		}

		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ShaderProgram);
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(m_ShaderProgram);
	}

	void OpenGLShader::Unbind()
	{
		glUseProgram(0);
	}

	uint32_t OpenGLShader::CompileShader(const std::string& shader, GLenum type)
	{
		const char* source = shader.c_str();

		uint32_t shaderId = glCreateShader(type);
		glShaderSource(shaderId, 1, &source, NULL);
		glCompileShader(shaderId);

		{
			int success;
			glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

			if (!success) {
				char info[512];
				glGetShaderInfoLog(shaderId, 512, NULL, info);
				LOG_CORE_ERROR(info)
			}

			GE_ASSERT(success, "Failed to compile shader");
		}

		return shaderId;
	}
}
