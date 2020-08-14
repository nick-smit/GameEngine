#include "pch.h"

#include "Core\Application.h"
#include "Core\Layer.h"

class MyLayer : public Engine::Layer {
public:
	MyLayer() : Layer("My Layer") {};

	virtual void OnAttach() override {
		LOG_INFO("Attach layer {0}", GetName())
	}

	virtual void OnDetach() override {
		LOG_INFO("Detach layer {0}", GetName())
	}

	virtual void OnUpdate() override {
	};

	virtual void OnEvent(Engine::Event& event) {
		LOG_INFO("Layer {0} got event {1}", GetName(), event)
	};
};

class MyApplication : public Engine::Application
{
public: 
	MyApplication(std::string name) : Engine::Application(name) {
		LOG_INFO("Application name: {0}", name);

		GetLayerStack()->PushLayer(new MyLayer());
	};
	
	~MyApplication() = default;
};

Engine::Application* Engine::CreateApplication()
{
	return new MyApplication("Game engine!");
}