#include "pch.h"
#include "Application.h"

namespace Engine {
	Application* Application::s_Instance = nullptr;

	Application::Application(std::string name)
		: m_Name(name) 
	{
		Logger::Init();
		LOG_CORE_INFO("Initializing engine v0.0.1")

		s_Instance = this;
		
		WindowProps windowProps;
		m_Window = WindowFactory::Create(windowProps);
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_LayerStack = new LayerStack();
	}

	Application::~Application()
	{
		delete m_LayerStack;

		Application::s_Instance = nullptr;
	}
	
	void Application::Run()
	{
		while (m_Running) {
			m_Window->OnUpdate();

			if (m_Minimized) continue;

			for (Layer* layer : *m_LayerStack) {
				layer->OnUpdate();
			}
		}
	}
	
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
		dispatcher.Dispatch<WindowBlurEvent>(BIND_EVENT_FN(Application::OnWindowBlur));
		dispatcher.Dispatch<WindowFocusEvent>(BIND_EVENT_FN(Application::OnWindowFocus));
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		// Todo something
		return false;
	}

	bool Application::OnWindowBlur(WindowBlurEvent& e)
	{
		m_Minimized = true;

		return false;
	}

	bool Application::OnWindowFocus(WindowFocusEvent& e)
	{
		m_Minimized = false;

		return false;
	}
}

