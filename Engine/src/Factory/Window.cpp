#include "pch.h"

#include "Window.h"
#include "Platform\Window\WindowsWindow.h"

namespace Engine {
	Scope<Window> WindowFactory::Create(const WindowProps& props)
	{
		return CreateScope<WindowsWindow>(props);
	}
}
