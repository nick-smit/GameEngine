#pragma once

#include "pch.h"
#include "Factory\Window.h"

#include "GLFW\glfw3.h"

namespace Engine {

	class WindowsWindow : public Window {
	private:
		struct WindowData {
			std::string Name;
			uint32_t Width = 0, Height = 0;

			std::function<void(Event&)> EventCallback;
		};

	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();
		
		virtual void OnUpdate() override;

		void SetEventCallback(const std::function<void(Event&)>& callback) override { m_Data.EventCallback = callback; };

		virtual const Math::Vec2 GetCursorPos() const override;

	private: 
		bool Init(const WindowProps& props);
		void Shutdown();
	private:
		GLFWwindow* m_GLFWwindow = nullptr;

		WindowData m_Data;
	};
}
