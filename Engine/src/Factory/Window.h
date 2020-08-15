#pragma once

#include "Core\Memory.h"
#include "Core\Window.h"

namespace Engine {

	class WindowFactory {
	public:
		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}