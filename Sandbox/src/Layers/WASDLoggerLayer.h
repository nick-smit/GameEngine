#pragma once

#include <Engine.h>

namespace Sandbox {
	class WASDLoggerLayer : public Engine::Layer {
	public:
		WASDLoggerLayer() : Layer("My Layer") {};

		virtual void OnUpdate() override;
	};
}