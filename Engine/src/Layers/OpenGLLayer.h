#pragma once

#include "Event\Event.h"
#include "Event\KeyEvent.h"
#include "Core\Layer.h"

namespace Engine {

	class OpenGLLayer : public Layer {
	public:
		OpenGLLayer();
		~OpenGLLayer();

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate() override;
		void OnEvent(Event& e) override;
		bool KeyPress(KeyPressEvent& e);

	private:
		double m_Red = 0.3f;

		uint32_t m_ShaderProgram;
	};

}