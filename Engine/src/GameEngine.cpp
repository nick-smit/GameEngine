#include "pch.h"

#include "Core\Application.h"

class MyApplication : public Engine::Application
{
public: 
	MyApplication(std::string name) : Engine::Application(name) {
		LOG_INFO("Application name: {0}", name)
	};
	
	~MyApplication() = default;
};

Engine::Application* Engine::CreateApplication()
{
	return new MyApplication("Game engine!");
}