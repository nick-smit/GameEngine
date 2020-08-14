#include "pch.h"
#include "LayerStack.h"

namespace Engine {
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers) {
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.push_back(layer);
		layer->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);

		GE_ASSERT(it == m_Layers.end(), "Layer was not found")
		if (it != m_Layers.end()) {
			layer->OnDetach();
			m_Layers.erase(it);
		}
	}
}
