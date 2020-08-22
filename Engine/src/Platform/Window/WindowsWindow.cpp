#include "pch.h"
#include "Event\ApplicationEvent.h"
#include "Event\MouseEvent.h"
#include "Event\KeyEvent.h"
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

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		#ifdef GE_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
		#endif

		/* Create a windowed mode window and its OpenGL context */
		m_GLFWwindow = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Name.c_str(), NULL, NULL);
		if (!m_GLFWwindow) {
			GE_CORE_ASSERT(m_GLFWwindow, "Failed to create a window");

			glfwTerminate();
			return false;
		}

		++windowCount;

		glfwSetWindowUserPointer(m_GLFWwindow, &m_Data);
		BindEvents();

		glfwMakeContextCurrent(m_GLFWwindow);

		SetVSync(props.VSync);

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

	void WindowsWindow::SetVSync(bool enabled)
	{
		m_Data.VSync = enabled;
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
	}

	const bool WindowsWindow::IsMouseButtonPressed(uint32_t mouseButtonCode) const
	{
		int glfwButton;
		switch (mouseButtonCode) {
		case GE_MOUSE_BUTTON_LEFT:
			glfwButton = GLFW_MOUSE_BUTTON_LEFT;
			break;
		case GE_MOUSE_BUTTON_RIGHT:
			glfwButton = GLFW_MOUSE_BUTTON_RIGHT;
			break;
		case GE_MOUSE_BUTTON_MIDDLE:
			glfwButton = GLFW_MOUSE_BUTTON_MIDDLE;
			break;
		case GE_MOUSE_BUTTON_4:
			glfwButton = GLFW_MOUSE_BUTTON_4;
			break;
		case GE_MOUSE_BUTTON_5:
			glfwButton = GLFW_MOUSE_BUTTON_5;
			break;
		case GE_MOUSE_BUTTON_6:
			glfwButton = GLFW_MOUSE_BUTTON_6;
			break;
		case GE_MOUSE_BUTTON_7:
			glfwButton = GLFW_MOUSE_BUTTON_7;
			break;
		case GE_MOUSE_BUTTON_8:
			glfwButton = GLFW_MOUSE_BUTTON_8;
			break;
		default:
			GE_CORE_ASSERT(false, "Unknown mouse button {0}", mouseButtonCode)
		}

		return glfwGetMouseButton(m_GLFWwindow, glfwButton) == GLFW_PRESS;
	}

	const Math::Vec2 WindowsWindow::GetCursorPos() const
	{
		double x, y;
		glfwGetCursorPos(m_GLFWwindow, &x, &y);

		int maxX, maxY;
		glfwGetWindowSize(m_GLFWwindow, &maxX, &maxY);

		if (x < 0 || x > maxX || y < 0 || y > maxY) {
			// Out of bounds
			return { -1, -1 };
		}

		return { x, y };
	}

	const bool WindowsWindow::IsKeyPressed(uint32_t keyCode) const
	{
		return glfwGetKey(m_GLFWwindow, (int)keyCode) == GLFW_PRESS;
	}

	void WindowsWindow::BindEvents()
	{
		// Window events
		glfwSetWindowCloseCallback(m_GLFWwindow, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			GE_CORE_ASSERT(&data, "Data object was not set correctly");

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetWindowSizeCallback(m_GLFWwindow, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			GE_CORE_ASSERT(&data, "Data object was not set correctly");

			WindowResizeEvent event((uint32_t)width, (uint32_t)height);
			data.EventCallback(event);
		});

		glfwSetWindowFocusCallback(m_GLFWwindow, [](GLFWwindow* window, int inFocus) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			GE_CORE_ASSERT(&data, "Data object was not set correctly");

			if (inFocus == GLFW_TRUE) {
				WindowFocusEvent event;
				data.EventCallback(event);
			}
			else {
				WindowBlurEvent event;
				data.EventCallback(event);
			}
		});
		// End window events

		// Mouse events
		glfwSetMouseButtonCallback(m_GLFWwindow, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			GE_CORE_ASSERT(&data, "Data object was not set correctly");

			int engineButton;
			switch (button) {
			case GLFW_MOUSE_BUTTON_LEFT:
				engineButton = GE_MOUSE_BUTTON_LEFT;
				break;
			case GLFW_MOUSE_BUTTON_RIGHT:
				engineButton = GE_MOUSE_BUTTON_RIGHT;
				break;
			case GLFW_MOUSE_BUTTON_MIDDLE:
				engineButton = GE_MOUSE_BUTTON_MIDDLE;
				break;
			case GLFW_MOUSE_BUTTON_4:
				engineButton = GE_MOUSE_BUTTON_4;
				break;
			case GLFW_MOUSE_BUTTON_5:
				engineButton = GE_MOUSE_BUTTON_5;
				break;
			case GLFW_MOUSE_BUTTON_6:
				engineButton = GE_MOUSE_BUTTON_6;
				break;
			case GLFW_MOUSE_BUTTON_7:
				engineButton = GE_MOUSE_BUTTON_7;
				break;
			case GLFW_MOUSE_BUTTON_8:
				engineButton = GE_MOUSE_BUTTON_8;
				break;
			default:
				GE_CORE_ASSERT(false, "Unknown mouse button {0}", button)
			}

			if (action == GLFW_PRESS) {
				MouseButtonPressEvent event(engineButton);
				data.EventCallback(event);
			}
			else if (action == GLFW_RELEASE) {
				MouseButtonReleaseEvent event(engineButton);
				data.EventCallback(event);
			}
		});

		glfwSetCursorPosCallback(m_GLFWwindow, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			GE_CORE_ASSERT(&data, "Data object was not set correctly");

			MouseMoveEvent event({ xPos, yPos });
			data.EventCallback(event);
		});

		glfwSetScrollCallback(m_GLFWwindow, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			GE_CORE_ASSERT(&data, "Data object was not set correctly");

			MouseScrollEvent event({ xOffset, yOffset });
			data.EventCallback(event);
		});
		// End mouse events

		// Key events
		glfwSetKeyCallback(m_GLFWwindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			GE_CORE_ASSERT(&data, "Data object was not set correctly");

			GE_CORE_ASSERT(key >= 0, "Got unknown key {0}, scancode: {1}", key, scancode)

			if (action == GLFW_PRESS) {
				KeyPressEvent event((uint32_t)key, false);
				data.EventCallback(event);
			}
			else if (action == GLFW_RELEASE) {
				KeyReleaseEvent event((uint32_t)key);
				data.EventCallback(event);
			}
			else {
				GE_CORE_ASSERT(action == GLFW_REPEAT, "Non implemented action given")

				KeyPressEvent eventb((uint32_t)key, true);
				data.EventCallback(eventb);
			}
		});

		glfwSetCharCallback(m_GLFWwindow, [](GLFWwindow* window, unsigned int keycode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			GE_CORE_ASSERT(&data, "Data object was not set correctly");

			KeyTypeEvent event((uint32_t)keycode);
			data.EventCallback(event);
		});
		// End key events
	}
}
