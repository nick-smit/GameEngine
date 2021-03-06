#pragma once

#include <string>
#include "Core\Window.h"
#include "Event\Event.h"
#include "Event\ApplicationEvent.h"
#include "Core\LayerStack.h"
#include "Core\Memory.h"

namespace Engine {
	class Application {
	public:
		Application(std::string name);

		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		inline static Application* GetInstance() { return s_Instance; };
		inline LayerStack* GetLayerStack() const { return m_LayerStack; };
		inline const std::string GetName() const { return m_Name; };
		inline Window* GetWindow() { return m_Window.get(); };

	private:
		static Application* s_Instance;

		std::string m_Name;
		bool m_Running = true;
		bool m_Minimized = false;

		Scope<Window> m_Window;
		LayerStack* m_LayerStack;
	};

	Application* CreateApplication();
}
