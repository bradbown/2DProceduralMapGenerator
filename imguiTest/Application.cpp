#include "Application.h"



Application::Application(int width, int height, sf::Color bgColour)
{
	this->width = width;
	this->height = height;

	this->bgColour = bgColour;
	map = new Map(256, 256);
}


Application::~Application()
{
	delete window;
}

void Application::Init()
{
	window = new sf::RenderWindow(sf::VideoMode(width, height), "");
	window->setVerticalSyncEnabled(true);
	ImGui::SFML::Init(*window);
}

void Application::Run()
{
	float colour[3] = { 0.f, 0.f, 0.f };
	char windowTitle[255] = "ImGui + SFML = <3";

	window->setTitle(windowTitle);
	window->resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
	sf::Clock deltaClock;
	while (window->isOpen()) 
	{
		sf::Event event;
		while (window->pollEvent(event)) 
		{
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) 
			{
				window->close();
			}
		}

		ImGui::SFML::Update(*window, deltaClock.restart());

		ImGui::Begin("Sample window"); // begin window

									   // Background color edit
		if (ImGui::ColorEdit3("Background color", colour))
		{
			// this code gets called if color value changes, so
			// the background color is updated automatically!
			bgColour.r = static_cast<sf::Uint8>(colour[0] * 255.f);
			bgColour.g = static_cast<sf::Uint8>(colour[1] * 255.f);
			bgColour.b = static_cast<sf::Uint8>(colour[2] * 255.f);
		}

		// Window title text edit
		ImGui::InputText("Window title", (char*)&windowTitle, 255);

		if (ImGui::Button("Update window title"))
		{
			// this code gets if user clicks on the button
			// yes, you could have written if(ImGui::InputText(...))
			// but I do this to show how buttons work :)
			window->setTitle(windowTitle);
		}

		ImGui::ShowTestWindow();

		ImGui::End(); // end window
		Update();
		Render();
	}

	ImGui::SFML::Shutdown();
}

void Application::Update()
{
	input.Update(*window);
	map->Update(*window, input);
}

void Application::Render()
{
	window->clear(bgColour); // fill background with color
	map->Draw(*window);
	ImGui::SFML::Render(*window);
	window->display();
}