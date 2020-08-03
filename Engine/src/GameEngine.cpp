#include "pch.h"

#include "Core\Application.h"

class MyApplication : public Engine::Application
{
public: 
	MyApplication(std::string name) : Engine::Application(name) {
		std::cout << "From MyApplication: " << this->GetName() << std::endl;
	};
	
	~MyApplication() = default;
};

Engine::Application* Engine::CreateApplication()
{
	return new MyApplication("Game engine!");
}