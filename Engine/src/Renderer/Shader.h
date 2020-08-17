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
	};

	class ShaderFactory {
	public:
		static Ref<Shader> FromFile(const std::string& filename);
		static Ref<Shader> FromSource(const std::string& vertexShader, const std::string& fragmentShader);
	};

}