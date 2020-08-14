#pragma once

#include "pch.h"
#include "Factory\Window.h"
#include "Event\Event.h"
#include "Event\ApplicationEvent.h"

namespace Engine {
	class Application {
	public:
		Application(std::string name);

		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnWindowBlur(WindowBlurEvent& e);
		bool OnWindowFocus(WindowFocusEvent& e);

		inline static Application* GetInstance() { return s_Instance; };
		inline const std::string GetName() const { return m_Name; };

	private:
		static Application* s_Instance;

		std::string m_Name;
		bool m_Running = true;
		bool m_Minimized = true;

		Scope<Window> m_Window;
	};

	Application* CreateApplication();
}
