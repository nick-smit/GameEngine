#pragma once

#include "Core\Memory.h"

namespace Engine {

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;
	};

	class IndexBufferFactory {
	public:
		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
	};

}
