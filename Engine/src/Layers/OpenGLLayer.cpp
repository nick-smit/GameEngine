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

		GLint nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		LOG_CORE_DEBUG("Max vertex attributes: {0}", nrAttributes)


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
		m_ShaderProgram = ShaderFactory::FromFile("assets/shaders/basic.vertex", "assets/shaders/basic.fragment");
	}

	void OpenGLLayer::OnDetach()
	{
	}

	void OpenGLLayer::OnUpdate()
	{
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		GLfloat vertices[] = {
			-0.5f, -0.25f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.25f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		};

		GLuint indices[] = {
			0, 1, 2,
		};

		GLuint elementBuffer;
		glGenBuffers(1, &elementBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		GLuint vertexBuffer;
		glGenBuffers(1, &vertexBuffer);

		GLuint vertexArray;
		glGenVertexArrays(1, &vertexArray);

		glBindVertexArray(vertexArray);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		m_ShaderProgram->Bind();

		//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
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
