#pragma once
#include "pch.h"

#include "Event\Event.h"

namespace Engine {
	struct WindowProps {
		uint32_t Width;
		uint32_t Height;
		std::string Name;

		WindowProps(const std::string& name,
			uint32_t width = 1280,
			uint32_t height = 720)
			: Name(name), Width(width), Height(height)
		{
		}

		WindowProps(uint32_t width = 1280, uint32_t height = 720)
			: Name("Unknown window"), Width(width), Height(height)
		{
		}
	};

	class Window {
	public:
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual void SetEventCallback(const std::function<void(Event&)>&) = 0;
	};

	class WindowFactory {
	public:
		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}