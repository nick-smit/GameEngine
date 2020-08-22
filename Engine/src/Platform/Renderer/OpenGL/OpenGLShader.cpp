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

			GE_CORE_ASSERT(success, "Failed to link program");
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

			GE_CORE_ASSERT(success, "Failed to compile shader");
		}

		return shaderId;
	}

	int32_t OpenGLShader::GetUniformLocation(const std::string& name) const
	{
		int32_t loc = glGetUniformLocation(m_ShaderProgram, name.c_str());
		GE_CORE_ASSERT(loc >= 0, "Could not find uniform name");

		return loc;
	}

	void OpenGLShader::SetInt1(const std::string& name, int32_t v1)
	{
		Bind();
		int32_t loc = GetUniformLocation(name);

		glUniform1i(loc, v1);
	}

	void OpenGLShader::SetInt2(const std::string& name, int32_t v1, int32_t v2)
	{
		Bind();
		int32_t loc = GetUniformLocation(name);

		glUniform2i(loc, v1, v2);
	}

	void OpenGLShader::SetInt3(const std::string& name, int32_t v1, int32_t v2, int32_t v3)
	{
		Bind();
		int32_t loc = GetUniformLocation(name);

		glUniform3i(loc, v1, v2, v3);
	}

	void OpenGLShader::SetInt4(const std::string& name, int32_t v1, int32_t v2, int32_t v3, int32_t v4)
	{
		Bind();
		int32_t loc = GetUniformLocation(name);

		glUniform4i(loc, v1, v2, v3, v4);
	}

	void OpenGLShader::SetUint1(const std::string& name, int32_t v1)
	{
		Bind();
		int32_t loc = GetUniformLocation(name);

		glUniform1ui(loc, v1);
	}

	void OpenGLShader::SetUint2(const std::string& name, int32_t v1, int32_t v2)
	{
		Bind();
		int32_t loc = GetUniformLocation(name);

		glUniform2ui(loc, v1, v2);
	}

	void OpenGLShader::SetUint3(const std::string& name, int32_t v1, int32_t v2, int32_t v3)
	{
		Bind();
		int32_t loc = GetUniformLocation(name);

		glUniform3ui(loc, v1, v2, v3);
	}

	void OpenGLShader::SetUint4(const std::string& name, int32_t v1, int32_t v2, int32_t v3, int32_t v4)
	{
		Bind();
		int32_t loc = GetUniformLocation(name);

		glUniform4ui(loc, v1, v2, v3, v4);
	}

	void OpenGLShader::SetFloat1(const std::string& name, float v1)
	{
		Bind();
		int32_t loc = GetUniformLocation(name);

		glUniform1f(loc, v1);
	}

	void OpenGLShader::SetFloat2(const std::string& name, float v1, float v2)
	{
		Bind();
		int32_t loc = GetUniformLocation(name);

		glUniform2f(loc, v1, v2);
	}

	void OpenGLShader::SetFloat3(const std::string& name, float v1, float v2, float v3)
	{
		Bind();
		int32_t loc = GetUniformLocation(name);

		glUniform3f(loc, v1, v2, v3);
	}

	void OpenGLShader::SetFloat4(const std::string& name, float v1, float v2, float v3, float v4)
	{
		Bind();
		int32_t loc = GetUniformLocation(name);

		glUniform4f(loc, v1, v2, v3, v4);
	}
}
