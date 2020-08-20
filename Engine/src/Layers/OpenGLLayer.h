#pragma once

#include "Event\Event.h"
#include "Event\KeyEvent.h"
#include "Core\Layer.h"
#include "Renderer\Shader.h"
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
		uint32_t m_Texture1 = 0;
		uint32_t m_Texture2 = 0;
		uint32_t m_Texture3 = 0;
	};

}