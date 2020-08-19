#pragma once

#include "Renderer\RenderCommand.h"

namespace Engine {

	class OpenGLRendererAPI : public RendererAPI {
	public:
		virtual void Init() override;
		virtual void Shutdown() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void SetClearColor(const Math::Vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const Ref<ElementBuffer>& elementBuffer) override;
	};

}
