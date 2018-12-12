#include "Application.h"
#include <iostream>

Application::Application(int width, int height)
{
	this->width = width;
	this->height = height;
	map = std::make_shared<Map>(512, 512);
}


Application::~Application()
{
}


void Application::Init()
{
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), "Map Generator", 7);
}

void Application::Run()
{
	while (window.get()->isOpen())
	{
		Update();
		Render();		
	}
}

void Application::Update()
{
	input.Update(window);
	map->Update(window, input);	
}

void Application::Render()
{
	window->clear();
	map->Draw(window);
	window->display();
}