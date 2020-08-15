#pragma once

#include "Core\Window.h"
#include "Math\Vector.h"

namespace Engine {

	class Input {
	public:
		static bool IsKeyPressed(uint32_t keyCode);

		static bool IsMouseButtonPressed(uint32_t mouseButton);
		static Math::Vec2 GetCursorPosition();
	private:
		static Window& s_Window;
	};

}