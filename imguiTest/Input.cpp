#include "Input.h"



Input::Input()
{
	mouseLeft = false;
}


Input::~Input()
{
}

void Input::Update(sf::RenderWindow& window)
{
	sf::Event e;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		window.close();
	}
	
	while (window.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::Resized:

			break;

		case sf::Event::MouseButtonPressed:

			if (e.mouseButton.button == sf::Mouse::Left)
			{
				mouseLeft = true;
			}
			break;

		case sf::Event::MouseButtonReleased:

			if (e.mouseButton.button == sf::Mouse::Left)
			{
				mouseLeft = false;
			}
			break;
		}
	}
}
