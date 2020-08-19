#pragma once

#include "Core\Memory.h"
#include "Renderer\VertexBuffer.h"
#include "Renderer\IndexBuffer.h"

#include <vector>

namespace Engine {

	class ElementBuffer {
	public:
		virtual ~ElementBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
	};

	class ElementBufferFactory {
	public:
		static Ref<ElementBuffer> Create();
	};

}
