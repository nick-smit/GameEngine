#pragma once

#include "Core\Math.h"

namespace Engine {

	class Renderer2D {
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene();

		static void DrawQuad(const Math::Vec3& position, const Math::Vec4& color);
	};

}
