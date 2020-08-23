#include "pch.h"
#include "OpenGLLayer.h"

#include "Event\KeyEvent.h"

#include "Renderer\Renderer2D.h"

#include <glad\glad.h>

namespace Engine {
	
	OpenGLLayer::OpenGLLayer() : Layer("OpenGLLayer")
	{
	}

	OpenGLLayer::~OpenGLLayer()
	{
	}

	void OpenGLLayer::OnAttach()
	{
		Renderer2D::Init();
	}

	void OpenGLLayer::OnDetach()
	{
	}

	void OpenGLLayer::OnUpdate()
	{
		Renderer2D::BeginScene();
		Renderer2D::DrawQuad({0.0f, 0.25f, 0.0f}, Math::Vec4(1, 0, 0, 1));
		Renderer2D::DrawQuad({0.250f, 0.0f, 0.0f}, Math::Vec4(0, 1, 0, 1));
	}

	void OpenGLLayer::OnEvent(Event& e)
	{
	}

}
