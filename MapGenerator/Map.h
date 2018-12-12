#pragma once

#include <SFML\Graphics.hpp>
#include <memory>
#include "Input.h"

#include <vector>
#include <iostream>

#include "FastNoiseSIMD.h"

#include <glm.hpp>
#include <gtx\gradient_paint.hpp>

class Map
{
public:

	Map(int width, int height);
	~Map();

	std::shared_ptr<sf::RectangleShape> map;

	void Update(std::shared_ptr<sf::RenderWindow>& window, Input& input);
	void Draw(std::shared_ptr<sf::RenderWindow>& window);

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

	int size = 512;

	float NormalizeNoise(float noise);

	bool inCircle(int centerX, int centerY, float radius, int x, int y);

	std::vector<float> GenerateFalloffMap(int size);
};

