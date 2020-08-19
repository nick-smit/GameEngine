#include "pch.h"
#include "OpenGLLayer.h"

#include "Event\KeyEvent.h"

#include "Renderer\RenderCommand.h"
#include "Renderer\ElementBuffer.h"
#include "Renderer\IndexBuffer.h"
#include "Renderer\VertexBuffer.h"

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
		
		RenderCommand::DrawIndexed(elementBuffer);
	}

	void OpenGLLayer::OnEvent(Event& e)
	{
	}

}
