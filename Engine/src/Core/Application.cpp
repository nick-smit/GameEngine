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
	}

	Application::~Application()
	{
		Application::s_Instance = nullptr;
	}
	
	void Application::Run()
	{
		while (m_Running) {
			m_Window->OnUpdate();
		}
	}
	
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}
}

