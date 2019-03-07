#pragma once

#include <memory>
#include <string.h>

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "Map.h"

class Application
{
public:
	Application(int width, int height, sf::Color);
	~Application();

	void Init();
	void Run();

protected:

	int width;
	int height;

	sf::Color bgColour;

	sf::RenderWindow* window;

private:

	Map * map;
	Input input;

	void Render();
	void Update();

};

