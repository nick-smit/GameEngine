// GameEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Core\Application.h"

int main()
{
	Engine::Application application("Game Engine!");

	std::cout << application.GetName() << std::endl;
	std::cout << Engine::Application::GetInstance()->GetName() << std::endl;

	std::cin.get();
}
