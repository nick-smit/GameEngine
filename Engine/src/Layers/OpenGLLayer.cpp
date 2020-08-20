#include "pch.h"
#include "OpenGLLayer.h"

#include "Event\KeyEvent.h"

#include "Renderer\RenderCommand.h"
#include "Renderer\ElementBuffer.h"
#include "Renderer\IndexBuffer.h"
#include "Renderer\VertexBuffer.h"

#include <glad\glad.h>
#include <stb_image.h>

namespace Engine {
	
	OpenGLLayer::OpenGLLayer() : Layer("OpenGLLayer")
	{
	}

	OpenGLLayer::~OpenGLLayer()
	{
	}

	void OpenGLLayer::OnAttach()
	{
		m_ShaderProgram = ShaderFactory::FromFile("assets/shaders/basic.vertex", "assets/shaders/basic.fragment");
		stbi_set_flip_vertically_on_load(true);

		{
			glGenTextures(1, &m_Texture1);
			glBindTexture(GL_TEXTURE_2D, m_Texture1);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			int32_t width, height, nrChannels;
			unsigned char* data = stbi_load("assets/textures/container.jpg", &width, &height, &nrChannels, 0);
			GE_CORE_ASSERT(data, "Could not load texture file");

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(data);
		}

		{
			glGenTextures(2, &m_Texture2);
			glBindTexture(GL_TEXTURE_2D, m_Texture2);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			int32_t width, height, nrChannels;
			unsigned char* data = stbi_load("assets/textures/awesomeface.png", &width, &height, &nrChannels, 0);
			GE_CORE_ASSERT(data, "Could not load texture file");

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(data);
		}

		m_ShaderProgram->SetInt1("texture1", 0);
		m_ShaderProgram->SetInt1("texture2", 1);
	}

	void OpenGLLayer::OnDetach()
	{
	}

	void OpenGLLayer::OnUpdate()
	{
		RenderCommand::SetClearColor({ 0.3f, 0.5f, 0.7f, 1.0f });
		RenderCommand::Clear();

		auto elementBuffer = ElementBufferFactory::Create();

		float quadVertices[] = {
			// Position         // Color                // Texture coords
			 0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Top right
			 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // Top left
			-0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Bottom left
			-0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // Bottom right
		};

		auto vertexBufferQuad = VertexBufferFactory::Create(quadVertices, sizeof(quadVertices));
		vertexBufferQuad->SetBufferLayout({
			{ ShaderDataType::Float3, "position" },
			{ ShaderDataType::Float4, "color" },
			{ ShaderDataType::Float2, "texCoords" },
		});

		elementBuffer->AddVertexBuffer(vertexBufferQuad);

		uint32_t quadIndices[] = {
			0, 1, 3,
				1, 2, 3,
		};

		auto indexBuffer = IndexBufferFactory::Create(quadIndices, 6);
		elementBuffer->SetIndexBuffer(indexBuffer);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_Texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_Texture2);

		m_ShaderProgram->Bind();
		
		RenderCommand::DrawIndexed(elementBuffer);
	}

	void OpenGLLayer::OnEvent(Event& e)
	{
	}

}
