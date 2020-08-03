// GameEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Core\Application.h"

Engine::Application* Engine::CreateApplication()
{
	return new Application("Game engine!");
}