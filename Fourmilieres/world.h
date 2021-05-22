#pragma once

#include <SFML/Graphics.hpp>
#include "tilemap.h"

class World
{
public:
	World();
	~World();

	// Update les différentes entitées en jeux
	void update();
	void draw(sf::RenderWindow& window);

	sf::Vector2u mapSizeInPixel();

private:
	TileMap _tilemap;
};