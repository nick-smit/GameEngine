#pragma once

#include <string>
#include "Core\Memory.h"

namespace Engine {

	class Shader {
	public:
		Shader() = default;
		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetInt1(const std::string& name, int32_t v1) = 0;
		virtual void SetInt2(const std::string& name, int32_t v1, int32_t v2) = 0;
		virtual void SetInt3(const std::string& name, int32_t v1, int32_t v2, int32_t v3) = 0;
		virtual void SetInt4(const std::string& name, int32_t v1, int32_t v2, int32_t v3, int32_t v4) = 0;

		virtual void SetUint1(const std::string& name, int32_t v1) = 0;
		virtual void SetUint2(const std::string& name, int32_t v1, int32_t v2) = 0;
		virtual void SetUint3(const std::string& name, int32_t v1, int32_t v2, int32_t v3) = 0;
		virtual void SetUint4(const std::string& name, int32_t v1, int32_t v2, int32_t v3, int32_t v4) = 0;

		virtual void SetFloat1(const std::string& name, float v1) = 0;
		virtual void SetFloat2(const std::string& name, float v1, float v2) = 0;
		virtual void SetFloat3(const std::string& name, float v1, float v2, float v3) = 0;
		virtual void SetFloat4(const std::string& name, float v1, float v2, float v3, float v4) = 0;

		void SetFloat2(const std::string& name, Math::Vec2 value) { SetFloat2(name, value.x, value.y); };
		void SetFloat3(const std::string& name, Math::Vec3 value) { SetFloat3(name, value.x, value.y, value.z); };
		void SetFloat4(const std::string& name, Math::Vec4 value) { SetFloat4(name, value.x, value.y, value.z, value.w); };

	};

	class ShaderFactory {
	public:
		static Ref<Shader> FromFile(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
		static Ref<Shader> FromSource(const std::string& vertexShader, const std::string& fragmentShader);
	};

}