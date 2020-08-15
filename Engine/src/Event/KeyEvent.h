#pragma once

#include "Event\Event.h"

namespace Engine {

	class KeyPressEvent : public Event {
	public:
		KeyPressEvent(uint32_t keyCode, bool isRepeat)
			: m_KeyCode(keyCode), m_IsRepeat(isRepeat) {};

		inline uint32_t GetKeyCode() const { return m_KeyCode; };
		inline bool IsRepeat() const { return m_IsRepeat; };

		EVENT_CLASS_TYPE(KeyPress)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
	private:
		uint32_t m_KeyCode;
		bool m_IsRepeat;
	};

	class KeyReleaseEvent : public Event {
	public:
		KeyReleaseEvent(uint32_t keyCode)
			: m_KeyCode(keyCode) {};

		inline uint32_t GetKeyCode() const { return m_KeyCode; };

		EVENT_CLASS_TYPE(KeyRelease)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
	private:
		uint32_t m_KeyCode;
	};

	class KeyTypeEvent : public Event {
	public:
		KeyTypeEvent(uint32_t keyCode)
			: m_KeyCode(keyCode) {};

		inline uint32_t GetKeyCode() const { return m_KeyCode; };

		EVENT_CLASS_TYPE(KeyTyped)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
	private:
		uint32_t m_KeyCode;
	};

}