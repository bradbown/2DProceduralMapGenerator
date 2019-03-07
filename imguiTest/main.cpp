#include "Application.h"

int main()
{
	Application app(1280, 720, sf::Color(0, 0, 0));

	app.Init();
	app.Run();
}