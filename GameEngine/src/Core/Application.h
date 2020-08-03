#pragma once

#include <string>

namespace Engine {
	class Application {
	public:
		Application(std::string name);

		virtual ~Application();

		inline static Application* GetInstance() { return s_Instance; };
		inline const std::string GetName() const { return m_Name; };

	private:
		static Application* s_Instance;

		std::string m_Name;
	};
}
