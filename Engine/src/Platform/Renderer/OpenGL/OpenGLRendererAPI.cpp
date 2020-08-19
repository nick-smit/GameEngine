#include "pch.h"
#include "Platform\Renderer\OpenGL\OpenGLRendererAPI.h"

#include <GLFW/glfw3.h>
#include <glad\glad.h>

namespace Engine {

	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         LOG_CORE_CRITICAL(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       LOG_CORE_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:          LOG_CORE_WARN(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: LOG_CORE_DEBUG(message); return;
		}

		GE_CORE_ASSERT(false, "Unknown severity level!");
	}

	void OpenGLRendererAPI::Init()
	{
		int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GE_ASSERT(success, "Failed tot initialize GLAD")

		LOG_CORE_INFO("Loaded OpenGL version {0}.{1}", GLVersion.major, GLVersion.minor)


		#ifdef GE_DEBUG
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(OpenGLMessageCallback, nullptr);

			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
		#endif
	}

	void OpenGLRendererAPI::Shutdown()
	{
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const Math::Vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<ElementBuffer>& elementBuffer)
	{
		elementBuffer->Bind();
		glDrawElements(GL_TRIANGLES, elementBuffer->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		elementBuffer->Unbind();
	}

}
