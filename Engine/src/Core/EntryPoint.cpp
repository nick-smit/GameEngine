#include "Application.h"
#include <iostream>

using namespace Engine;

int main()
{
	Application* application = CreateApplication();

	std::cout << "Application started!" << std::endl;
	std::cout << "Application name: " << application->GetName() << std::endl;

	std::cin.get();
}
