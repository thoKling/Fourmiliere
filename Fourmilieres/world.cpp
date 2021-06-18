#include "World.h"
#include "config.h"

World::World(sf::Vector2u mapSize, int obstaclesNbr, int foodNbr, int evaporationRate)
{
	_tilemap.generateMap(mapSize, obstaclesNbr);
	_foodManager.generateFood(foodNbr, _tilemap);
	_anthillManager.createAnthill(*this, sf::Vector2u(20, 20), evaporationRate);
}

World::~World()
{
}

void World::update()
{
	_anthillManager.update();

}

void World::turnUpdate() {
	_anthillManager.turnUpdate();
}

void World::draw(sf::RenderWindow& window)
{
	window.draw(_tilemap);
	_foodManager.draw(window);
	_anthillManager.draw(window);
}

FoodManager & World::getFoodManager()
{
	return _foodManager;
}

TileMap & World::getTileMap()
{
	return _tilemap;
}

AnthillManager & World::getAnthillManager()
{
	return _anthillManager;
}

sf::Vector2u World::mapSizeInPixel()
{
	sf::Vector2u mapSize = _tilemap.getMapSize();
	return sf::Vector2u(mapSize.x * 64, mapSize.y * 64);
}
