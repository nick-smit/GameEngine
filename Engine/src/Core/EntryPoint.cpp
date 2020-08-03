#include "pch.h"
#include "Application.h"

using namespace Engine;

int main()
{
	Application* application = CreateApplication();

	application->Run();

	delete application;
}
