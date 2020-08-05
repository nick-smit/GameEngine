#pragma once

#include "pch.h"
#include "Factory\Window.h"

#include "GLFW\glfw3.h"

namespace Engine {
	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();
		
		virtual void OnUpdate() override;
	private: 
		bool Init(const WindowProps& props);
		void Shutdown();
	private:
		GLFWwindow* m_GLFWwindow = nullptr;

		struct WindowData {
			std::string Name;
			uint32_t Width, Height;
		};
	
		WindowData m_Data;
	};
}
