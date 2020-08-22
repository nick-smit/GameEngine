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
		
		virtual void SetInt1(const std::string& name, int32_t v1) override;
		virtual void SetInt2(const std::string& name, int32_t v1, int32_t v2) override;
		virtual void SetInt3(const std::string& name, int32_t v1, int32_t v2, int32_t v3) override;
		virtual void SetInt4(const std::string& name, int32_t v1, int32_t v2, int32_t v3, int32_t v4) override;
		virtual void SetIntArray(const std::string& name, int32_t* data, uint32_t count) override;

		virtual void SetUint1(const std::string& name, int32_t v1) override;
		virtual void SetUint2(const std::string& name, int32_t v1, int32_t v2) override;
		virtual void SetUint3(const std::string& name, int32_t v1, int32_t v2, int32_t v3) override;
		virtual void SetUint4(const std::string& name, int32_t v1, int32_t v2, int32_t v3, int32_t v4) override;

		virtual void SetFloat1(const std::string& name, float v1) override;
		virtual void SetFloat2(const std::string& name, float v1, float v2) override;
		virtual void SetFloat3(const std::string& name, float v1, float v2, float v3) override;
		virtual void SetFloat4(const std::string& name, float v1, float v2, float v3, float v4) override;

	private:
		uint32_t CompileShader(const std::string& shader, GLenum type);
		int32_t GetUniformLocation(const std::string& name) const;

	private:
		uint32_t m_ShaderProgram;
	};

}