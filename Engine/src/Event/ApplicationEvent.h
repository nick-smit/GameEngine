#pragma once

#include "pch.h"
#include "Event\Event.h"

namespace Engine {
	
	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			: m_Width(width), m_Height(height) {};

		inline const uint32_t GetWidth() const { return m_Width; }
		inline const uint32_t GetHeight() const { return m_Height; }

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		uint32_t m_Width, m_Height;
	};

	class WindowFocusEvent : public Event {
	public:
		WindowFocusEvent() = default;

		EVENT_CLASS_TYPE(WindowFocus)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class WindowBlurEvent : public Event {
	public:
		WindowBlurEvent() = default;

		EVENT_CLASS_TYPE(WindowBlur)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

}
