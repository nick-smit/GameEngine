#include "pch.h"
#include "OpenGLLayer.h"

#include "Event\KeyEvent.h"

#include <GLFW/glfw3.h>
#include <glad\glad.h>

#include "Renderer\ElementBuffer.h"
#include "Renderer\IndexBuffer.h"
#include "Renderer\VertexBuffer.h"

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
		glClearColor(0.3f, 0.5f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		auto elementBuffer = ElementBufferFactory::Create();

		float quadVertices[] = {
			-0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		};
		auto vertexBufferQuad = VertexBufferFactory::Create(quadVertices, sizeof(quadVertices));
		vertexBufferQuad->SetBufferLayout({
			{ ShaderDataType::Float3, "position" },
			{ ShaderDataType::Float4, "color" }
		});

		elementBuffer->AddVertexBuffer(vertexBufferQuad);

		uint32_t quadIndices[] = {
			0, 1, 3,
				1, 2, 3,
		};

		auto indexBuffer = IndexBufferFactory::Create(quadIndices, 6);
		elementBuffer->SetIndexBuffer(indexBuffer);

		m_ShaderProgram->Bind();
		elementBuffer->Bind();
		glDrawElements(GL_TRIANGLES, elementBuffer->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
		elementBuffer->Unbind();
	}

	void OpenGLLayer::OnEvent(Event& e)
	{
	}

}
