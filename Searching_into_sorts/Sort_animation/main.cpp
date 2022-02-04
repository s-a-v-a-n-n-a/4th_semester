#include <cstdio>
#include <cstdlib>

#include "Application/Application.hpp"

int main()
{
    std::srand(std::time(0));
	 
	Application::get_app()->launch();

	return 0;
}
