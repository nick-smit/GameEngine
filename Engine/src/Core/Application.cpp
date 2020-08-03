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
	}

	Application::~Application()
	{
		Application::s_Instance = nullptr;
	}
	
	void Application::Run()
	{
		while (m_Running) {
			// do stuff
		}

		#ifdef GE_DEBUG
			// Wait for user input before closing the console window.
			std::cin.get();
		#endif
	}
}

