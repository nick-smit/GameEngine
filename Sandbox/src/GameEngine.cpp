#include <Engine.h>
#include "Layers\WASDLoggerLayer.h"

namespace Sandbox {
	class MyApplication : public Engine::Application
	{
	public:
		MyApplication(std::string name) : Engine::Application(name) {
			LOG_INFO("Application name: {0}", name);

			GetLayerStack()->PushLayer(new WASDLoggerLayer());
		};

		~MyApplication() = default;
	};

}

Engine::Application* Engine::CreateApplication()
{
	return new Sandbox::MyApplication("Game engine!");
}