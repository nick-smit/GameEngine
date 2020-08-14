#pragma once
#include "pch.h"

#include "Event\Event.h"

namespace Engine {
	struct WindowProps {
		uint32_t Width;
		uint32_t Height;
		std::string Name;
		bool VSync;

		WindowProps(const std::string& name,
			uint32_t width = 1280,
			uint32_t height = 720,
			bool vsync = true)
			: Name(name), Width(width), Height(height), VSync(vsync)
		{
		}

		WindowProps(uint32_t width = 1280, uint32_t height = 720)
			: Name("Unknown window"), Width(width), Height(height), VSync(true)
		{
		}
	};

	class Window {
	public:
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual void SetEventCallback(const std::function<void(Event&)>&) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool VSyncEnabled() const = 0;

		virtual const Math::Vec2 GetCursorPos() const = 0;
	};

	class WindowFactory {
	public:
		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}