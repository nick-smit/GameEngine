#pragma once

#include <ostream>
#include <string>
#include "Event/Event.h"

namespace Engine {

	class Layer {
	public:
		Layer(const std::string& name = "Unnamed layer") : m_Name(name) {};
		virtual ~Layer() = default;

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate() {};
		virtual void OnEvent(Event& event) {};

		const std::string& GetName() const { return m_Name; }
	private:
		std::string m_Name;
	};
}