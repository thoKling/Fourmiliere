#pragma once

#include <vector>
#include "food.h"

class TileMap;

class FoodManager
{
public:
	FoodManager();
	~FoodManager();

	void update();
	void draw(sf::RenderWindow& window);

	void generateFood(unsigned int numberOfFood, TileMap& tileMap);
	bool isFoodThere(sf::Vector2u position);
	void removeFood(sf::Vector2u position);

	int harvest(sf::Vector2u position);

private:
	std::vector<Food*> _foodList;
};