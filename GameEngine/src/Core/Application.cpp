#include "Application.h"

#include <iostream>

namespace Engine {
	Application* Application::s_Instance = nullptr;

	Application::Application(std::string name)
		: m_Name(name) {
		s_Instance = this;
	}

	Application::~Application()
	{
		Application::s_Instance = nullptr;
	}
}
