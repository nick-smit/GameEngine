#pragma once

#include "Event\Event.h"

namespace Engine {
	class MouseButtonPressEvent : public Event {
	public:
		MouseButtonPressEvent(int button)
			: m_Button(button) {};

		inline int GetMouseButton() const { return m_Button; };

		EVENT_CLASS_TYPE(MouseButtonPressed)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryMouseButton)
	private:
		int m_Button;
	};

	class MouseButtonReleaseEvent : public Event {
	public:
		MouseButtonReleaseEvent(int button)
			: m_Button(button) {};

		inline int GetMouseButton() const { return m_Button; };

		EVENT_CLASS_TYPE(MouseButtonReleased)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryMouseButton)
	private:
		int m_Button;
	};

	class MouseMoveEvent : public Event {
	public:
		MouseMoveEvent(Math::Vec2 position)
			: m_Position(position) {};

		inline const Math::Vec2 GetPosition() const { return m_Position; };

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse)
	
	private:
		Math::Vec2 m_Position;
	};

	class MouseScrollEvent : public Event {
	public:
		MouseScrollEvent(Math::Vec2 scrollOffset)
			: m_ScrollOffset(scrollOffset) {};

		inline const Math::Vec2 GetScrollOffset() const { return m_ScrollOffset; };

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse)
	private:
		Math::Vec2 m_ScrollOffset;
	};
}
