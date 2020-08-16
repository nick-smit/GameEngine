#include "pch.h"
#include "OpenGLLayer.h"

#include "Event\KeyEvent.h"

#include <GLFW/glfw3.h>
#include <glad\glad.h>

namespace Engine {
	
	OpenGLLayer::OpenGLLayer() : Layer("OpenGLLayer")
	{
		int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GE_ASSERT(success, "Failed tot initialize GLAD")

		LOG_CORE_INFO("Loaded OpenGL version {0}.{1}", GLVersion.major, GLVersion.minor)

		int width = (int)Application::GetInstance()->GetWindow()->GetWidth();
		int height = (int)Application::GetInstance()->GetWindow()->GetHeight();
		// Define the viewport dimensions
		glViewport(0, 0, width, height);
	}

	OpenGLLayer::~OpenGLLayer()
	{
	}

	void OpenGLLayer::OnAttach()
	{
	}

	void OpenGLLayer::OnDetach()
	{
	}

	void OpenGLLayer::OnUpdate()
	{
		glClearColor(m_Red, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressEvent>(BIND_EVENT_FN(OpenGLLayer::KeyPress));
	}

	bool OpenGLLayer::KeyPress(KeyPressEvent& e)
	{
		if (e.GetKeyCode() == GE_KEY_UP) {
			if (m_Red < 1.0f) {
				m_Red += 0.01f;
			}
		}
		else if (e.GetKeyCode() == GE_KEY_DOWN) {
			if (m_Red > 0.0f) {
				m_Red -= 0.01f;
			}
		}

		return false;
	}

}
