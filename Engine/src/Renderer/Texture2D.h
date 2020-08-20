#pragma once

#include <string>
#include "Core\Memory.h"

namespace Engine {
	enum class TextureDataFormat {
		RGB, RGBA,
	};

	class Texture2D {
	public:
		virtual ~Texture2D() = default;

		virtual void Bind(uint32_t slot) = 0;
		virtual void Unbind(uint32_t ) = 0;

		virtual void SetData(void* data, size_t size) = 0;

		virtual bool operator==(const Texture2D& other) const = 0;

	public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
		static Ref<Texture2D> FromFile(const std::string& file);
	};

}
