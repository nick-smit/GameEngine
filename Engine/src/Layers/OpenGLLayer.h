#pragma once

#include "Event\Event.h"
#include "Event\KeyEvent.h"
#include "Core\Layer.h"
#include "Renderer\Shader.h"
#include "Renderer\Texture2D.h"
#include "Core\Memory.h"

namespace Engine {

	class OpenGLLayer : public Layer {
	public:
		OpenGLLayer();
		~OpenGLLayer();

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate() override;
		void OnEvent(Event& e) override;
	private:
		double m_Red = 0.3f;

		Ref<Shader> m_ShaderProgram = nullptr;
		Ref<Texture2D> m_ContainerTexture = nullptr;
		Ref<Texture2D> m_SmileTexture = nullptr;
	};

}