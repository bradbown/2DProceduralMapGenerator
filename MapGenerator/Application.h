#pragma once

#include <memory>
#include <SFML\Graphics.hpp>

#include "Map.h"
#include "Input.h"

class Application
{
public:
	Application(int width, int height);
	~Application();

	void Init();
	void Run();

protected:

	int width, height;

	std::shared_ptr<sf::RenderWindow> window;

private:

	std::shared_ptr<Map> map;
	Input input;


	void Render();
	void Update();
};

