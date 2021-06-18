#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

class PheromonesManager
{
public:
	PheromonesManager(sf::Vector2u mapSize, int evaporationRate);
	~PheromonesManager();

	void setPheromones(sf::Vector2u position, int level);
	int getPheromones(sf::Vector2u position);

	void turnUpdate();

private:
	std::vector<std::vector<int>> _pheromones;
	int _evaporationRate = 0;
};

