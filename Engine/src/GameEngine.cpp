#include "pch.h"

#include "Core\Application.h"

Engine::Application* Engine::CreateApplication()
{
	return new Application("Game engine!");
}