#include "Map.h"

Map::Map(int width, int height)
{
	map = std::make_shared<sf::RectangleShape>(sf::Vector2f(width, height));
	map->setOrigin(width / 2, height / 2);
	map->setPosition(width / 2, height / 2);

	newMousePos = sf::Vector2f(0.0f, 0.0f);
	oldMousePos = sf::Vector2f(0.0f, 0.0f);
	mouseClicked = false;

	heightMapImage.create(size, size);

	this->width = width;
	this->height = height;

	initMap();
}


Map::~Map()
{
	
}

void Map::Update(std::shared_ptr<sf::RenderWindow>& window, Input& input)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		map->move(-0.1f, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		map->move(0.1f, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		map->move(0.0f, -0.1f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		map->move(0.0f, 0.1f);
	}

	if (input.mouseLeft)
	{
		newMousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));

		if (!mouseClicked)
		{
			mouseClicked = true;
			oldMousePos = newMousePos;
		}

		if (map->getGlobalBounds().contains(newMousePos) && oldMousePos != sf::Vector2f(0.0f, 0.0f))
		{			
			sf::Vector2f mousePosDiff = sf::Vector2f(map->getPosition().x + (newMousePos.x - oldMousePos.x),
				map->getPosition().y + (newMousePos.y - oldMousePos.y));

			map->setPosition(mousePosDiff);
		}

		oldMousePos = newMousePos;
	}
	if (!input.mouseLeft)
	{
		mouseClicked = false;
	}
}

void Map::Draw(std::shared_ptr<sf::RenderWindow>& window)
{
	window->draw(*map);
}

void Map::initMap()
{
	noise = FastNoiseSIMD::NewFastNoiseSIMD();
	noise->SetNoiseType(FastNoiseSIMD::SimplexFractal);
	
	noise->SetSeed(1552);
	noise->SetFrequency(0.02f);
	noise->SetFractalType(FastNoiseSIMD::FractalType::FBM);
	noise->SetFractalOctaves(5);
	noise->SetFractalLacunarity(2.0f);
	noise->SetFractalGain(0.5f);
	noiseMap = noise->GetSimplexFractalSet(0, 0, 0, size, size, size);
	std::vector<float> falloffMap = GenerateFalloffMap(512);
	float radialGradient;
	int centerX = 256;
	int centreY = 256;
	float radius = 256.f;
	int focalX = 256;
	int focalY = 256;

	int index = 0;

	for (size_t y = 0; y < size; y++)
	{
		for (size_t x = 0; x < size; x++)
		{
			
			//if(inCircle(centerX, centreY, radius, x, y))
			//{
			//	radialGradient = glm::radialGradient(glm::vec2(centerX, centreY), radius, glm::vec2(focalX, focalY), glm::vec2(x, y));
			//}
			//else
			//{
			//	radialGradient = 1;
			//}
			//float normalizedNoise = radialGradient;
			//std::cout << normalizedNoise << std::endl;
			float normalizedNoise = NormalizeNoise(noiseMap[index]);
			
			if (normalizedNoise < 0.5f)
			{
				heightMapImage.setPixel(x, y, sf::Color(26, 156, 204, 255));
			}
			else if (0.5f <= normalizedNoise && normalizedNoise < 0.55f)
			{
				heightMapImage.setPixel(x, y, sf::Color(219, 214, 61, 255));
			}
			else if (0.55f <= normalizedNoise && normalizedNoise < 0.7f)
			{
				heightMapImage.setPixel(x, y, sf::Color(20, 188, 9, 255));
			}
			else if (0.7f <= normalizedNoise && normalizedNoise < 0.9f)
			{
				heightMapImage.setPixel(x, y, sf::Color(8, 89, 3, 255));
			}
			else if (0.9f <= normalizedNoise && normalizedNoise < 1.f)
			{
				heightMapImage.setPixel(x, y, sf::Color(89, 58, 2, 255));
			}
			//else if (0.9f <= normalizedNoise && normalizedNoise < 0.95f)
			//{
			//	heightMapImage.setPixel(x, y, sf::Color(81, 79, 76, 255));
			//}
			//else if (0.95f <= normalizedNoise && normalizedNoise <= 1.f)
			//{
			//	heightMapImage.setPixel(x, y, sf::Color(255, 255, 255, 255));
			//}
			else 
			{
				heightMapImage.setPixel(x, y, sf::Color(normalizedNoise * 255, normalizedNoise * 255, normalizedNoise * 255, 255));
			}
			
			index++;	
		}
	}

	//FastNoiseSIMD::FreeNoiseSet(noiseMap);
	//delete noiseMap;
	//delete noise;	

	heightMap.loadFromImage(heightMapImage);
	map->setTexture(&heightMap);
}

float Map::NormalizeNoise(float noise)
{
	float min = -1.0;
	float max = 1.0;

	float normalized = (noise - min) / (max - min);
	
	return normalized;
}

bool Map::inCircle(int centerX, int centerY, float radius, int x, int y)
{
	if (glm::pow2(x - centerX) + glm::pow2(y - centerY) <= glm::pow2(radius))
	{
		return true;
	}

	return false;
}
std::vector<float> Map::GenerateFalloffMap(int size)
{
	std::vector<float> map = std::vector<float>(size);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			float x = i / (float)size * 2 - 1;
			float y = j / (float)size * 2 - 1;

			float value = glm::max(glm::abs(x), glm::abs(y));
			map.push_back(value);
		}
	}
	return map;
}

