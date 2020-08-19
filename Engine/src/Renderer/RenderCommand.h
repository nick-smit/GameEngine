#pragma once

#include "Core\Memory.h"
#include "Renderer\ElementBuffer.h"

namespace Engine {

	class RendererAPI {
	public:
		virtual void Init() = 0;
		virtual void Shutdown() = 0;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const Math::Vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<ElementBuffer>& elementBuffer) = 0;

		static Scope<RendererAPI> Create();
	};

	class RenderCommand {
	public:
		static void Init() { s_RendererAPI->Init(); };
		static void Shutdown() { s_RendererAPI->Shutdown(); };
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_RendererAPI->SetViewport(x, y, width, height); };
		static void SetClearColor(const Math::Vec4& color) { s_RendererAPI->SetClearColor(color); };
		static void Clear() { s_RendererAPI->Clear(); };
		static void DrawIndexed(const Ref<ElementBuffer>& elementBuffer) { s_RendererAPI->DrawIndexed(elementBuffer); };

	private:
		static Scope<RendererAPI> s_RendererAPI;
	};

}
