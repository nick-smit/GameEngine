#include "pch.h"
#include "Application.h"

#include "GLFW\glfw3.h"

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
		auto success = glfwInit();
		GE_CORE_ASSERT(success, "Failed to initialize GLFW")

		/* Create a windowed mode window and its OpenGL context */
		GLFWwindow* window = glfwCreateWindow(640, 480, m_Name.c_str(), NULL, NULL);
		if (!window) {
			GE_CORE_ASSERT(window, "Failed to create a window")

			glfwTerminate();
			return;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		while (!glfwWindowShouldClose(window)) {

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		glfwTerminate();


		#ifdef GE_DEBUG
			// Wait for user input before closing the console window.
			std::cin.get();
		#endif
	}
}

