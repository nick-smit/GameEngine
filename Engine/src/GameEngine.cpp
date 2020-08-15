#include "pch.h"

#include "Core\Application.h"
#include "Core\Layer.h"
#include "Core\Memory.h"
#include "Core\Input.h"

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
		if (Engine::Input::IsKeyPressed(GE_KEY_W)) {
			LOG_INFO("W")
		}
		
	};

	virtual void OnEvent(Engine::Event& event) {
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