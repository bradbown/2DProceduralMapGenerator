#pragma once

#include <memory>
#include <SFML\Graphics.hpp>

class Input
{
public:
	Input();
	~Input();

	void Update(std::shared_ptr<sf::RenderWindow>& window);

	bool mouseLeft;

};

