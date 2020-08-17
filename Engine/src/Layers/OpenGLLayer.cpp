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
		const char* vertexShaderSource = "#version 330 core\n"
			"\n"
			"layout (location = 0) in vec3 position;\n"
			"\n"
			"void main() {\n"
			"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
			"}";
		
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		{
			int success;
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
			if (!success) {
				GLchar info[512];
				glGetShaderInfoLog(vertexShader, 512, NULL, info);

				LOG_CORE_ERROR(info)
			}
		}

		const char* fragmentShaderSource = "#version 330 core\n"
			"\n"
			"out vec4 color;\n"
			"\n"
			"void main() {\n"
			"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}";

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		{
			int success;
			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
			if (!success) {
				GLchar info[512];
				glGetShaderInfoLog(fragmentShader, 512, NULL, info);

				LOG_CORE_ERROR(info)
			}
		}

		m_ShaderProgram = glCreateProgram();
		glAttachShader(m_ShaderProgram, vertexShader);
		glAttachShader(m_ShaderProgram, fragmentShader);
		glLinkProgram(m_ShaderProgram);

		int success;
		glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			GLchar info[512];
			glGetProgramInfoLog(m_ShaderProgram, 512, NULL, info);
			LOG_CORE_ERROR(info)
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void OpenGLLayer::OnDetach()
	{
	}

	void OpenGLLayer::OnUpdate()
	{
		glClearColor(m_Red, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		GLfloat vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f,
		};

		GLuint vertexBuffer;
		glGenBuffers(1, &vertexBuffer);



		GLuint vertexArray;
		glGenVertexArrays(1, &vertexArray);

		glBindVertexArray(vertexArray);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glUseProgram(m_ShaderProgram);

		glDrawArrays(GL_TRIANGLES, 0, 3);
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
