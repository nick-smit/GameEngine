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

			bool VSync = true;

			std::function<void(Event&)> EventCallback;
		};

	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();
		
		virtual void OnUpdate() override;

		void SetEventCallback(const std::function<void(Event&)>& callback) override { m_Data.EventCallback = callback; };
		virtual void SetVSync(bool enabled) override;

		virtual const bool IsMouseButtonPressed(uint32_t mouseButtonCode) const override;
		virtual const Math::Vec2 GetCursorPos() const override;
		virtual const bool IsKeyPressed(uint32_t keyCode) const override;

		inline bool VSyncEnabled() const override { return m_Data.VSync; };
		inline uint32_t GetWidth() const override { return m_Data.Width; };
		inline uint32_t GetHeight() const override { return m_Data.Height; };

	private: 
		bool Init(const WindowProps& props);
		void Shutdown();
		void BindEvents();
	private:
		GLFWwindow* m_GLFWwindow = nullptr;

		WindowData m_Data;
	};
}
