#include "pch.h"
#include "Core\Application.h"
#include "Input.h"

namespace Engine {
	bool Input::IsKeyPressed(uint32_t keyCode)
	{
		return Application::GetInstance()->GetWindow()->IsKeyPressed(keyCode);
	}
	
	bool Input::IsMouseButtonPressed(uint32_t mouseButton)
	{
		return false;
	}

	Math::Vec2 Input::GetCursorPosition()
	{
		return Application::GetInstance()->GetWindow()->GetCursorPos();
	}
}

