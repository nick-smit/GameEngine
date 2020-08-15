#include "WASDLoggerLayer.h"
#include <Engine.h>

namespace Sandbox {
	void WASDLoggerLayer::OnUpdate()
	{
		if (Engine::Input::IsKeyPressed(GE_KEY_W)) {
			LOG_INFO("W");
		}
			
		if (Engine::Input::IsKeyPressed(GE_KEY_A)) {
			LOG_INFO("A");
		}
			
		
		if (Engine::Input::IsKeyPressed(GE_KEY_S)) {
			LOG_INFO("S");
		}
			

		if (Engine::Input::IsKeyPressed(GE_KEY_D)) {
			LOG_INFO("D");
		}
			
	}
}