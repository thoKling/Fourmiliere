#pragma once

#include <vector>
#include "anthill.h"

class TileMap;
class FoodManager;

class AnthillManager
{
public:
	AnthillManager();
	~AnthillManager();

	void update();

	void turnUpdate();

	void draw(sf::RenderWindow& window);

	void createAnthill(World& world, sf::Vector2u position);

private:
	std::vector<Anthill*> _anthillList;
};