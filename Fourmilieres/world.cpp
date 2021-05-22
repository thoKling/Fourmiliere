#include "World.h"

World::World()
{
	_tilemap.generateMap(sf::Vector2u(64, 64), 1000, 500);
}

World::~World()
{
}

void World::update()
{
}

void World::draw(sf::RenderWindow& window)
{
	window.draw(_tilemap);
}

sf::Vector2u World::mapSizeInPixel()
{
	sf::Vector2u mapSize = _tilemap.getMapSize();
	return sf::Vector2u(mapSize.x * 64, mapSize.y * 64);
}
