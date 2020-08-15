#include "pch.h"
#include "Application.h"

#include "Factory\Window.h"
#include "Core\Input.h"

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

		GE_ASSERT(!e.IsHandled(), "Application should never handle an event.")

		for (auto it = m_LayerStack->end(); it != m_LayerStack->begin(); ) {
			(*--it)->OnEvent(e);
		
			if (e.IsHandled()) 
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		return false;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 && e.GetHeight() == 0) {
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;

		return false;
	}
}

