#pragma once

#include <SFML\Graphics.hpp>
#include <memory>
#include "Input.h"

#include <vector>
#include <iostream>

#include "FastNoiseSIMD.h"
#include "imgui.h"
#include "imgui-SFML.h"

#include <glm.hpp>
#include <gtx\gradient_paint.hpp>

class Map
{
public:

	Map(int width, int height);
	~Map();

	sf::RectangleShape* map;
	
	void Update(sf::RenderWindow& window, Input& input);
	void Draw(sf::RenderWindow& window);

	sf::Image heightMapImage;


private:

	sf::Texture heightMap;

	sf::Vector2f newMousePos;
	sf::Vector2f oldMousePos;
	
	bool mouseClicked;

	int width, height;

	FastNoiseSIMD* noise;
	float* noiseMap;
	
	void initMap();

	int size = 32;

	float NormalizeNoise(float noise);

	bool inCircle(int centerX, int centerY, float radius, int x, int y);

	std::vector<float> GenerateFalloffMap(int size);

	ImGuiWindowFlags window_flags = 0;

	bool mapVisible;
	std::string buttonText;
};

