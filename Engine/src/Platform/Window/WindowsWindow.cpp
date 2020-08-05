#include "pch.h"
#include "WindowsWindow.h"

namespace Engine {
	static int windowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		LOG_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		LOG_CORE_DEBUG("Destroying window");
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		/* Swap front and back buffers */
		glfwSwapBuffers(m_GLFWwindow);

		/* Poll for and process events */
		glfwPollEvents();
	}

	bool WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Name = props.Name;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		LOG_CORE_INFO("Creating window {0}, width: {1}, height: {2}", m_Data.Name, m_Data.Width, m_Data.Height)

		if (windowCount == 0) {
			auto success = glfwInit();
			GE_CORE_ASSERT(success, "Failed to initialize GLFW");

			if (!success) {
				return false;
			}

			glfwSetErrorCallback(GLFWErrorCallback);
		}

		/* Create a windowed mode window and its OpenGL context */
		m_GLFWwindow = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Name.c_str(), NULL, NULL);
		if (!m_GLFWwindow) {
			GE_CORE_ASSERT(m_GLFWwindow, "Failed to create a window");

			glfwTerminate();
			return false;
		}

		++windowCount;

		// TODO: Move to GraphicsContext
		/* Make the window's context current */
		glfwMakeContextCurrent(m_GLFWwindow);

		return true;
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_GLFWwindow);
		--windowCount;

		if (windowCount == 0) {
			glfwTerminate();
		}
	}
}
