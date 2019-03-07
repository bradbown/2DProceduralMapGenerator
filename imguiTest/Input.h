#pragma once

#include <memory>
#include <SFML\Graphics.hpp>

class Input
{
public:
	Input();
	~Input();

	void Update(sf::RenderWindow& window);

	bool mouseLeft;

};

