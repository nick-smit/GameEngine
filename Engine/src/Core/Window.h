#pragma once

#include <functional>
#include "Math\Vector.h"
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

		virtual const bool IsKeyPressed(uint32_t keyCode) const = 0;
		virtual const bool IsMouseButtonPressed(uint32_t mouseButtonCode) const = 0;
		virtual const Math::Vec2 GetCursorPos() const = 0;
	};
}
