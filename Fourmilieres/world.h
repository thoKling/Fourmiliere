#pragma once

#include <SFML/Graphics.hpp>
#include "tilemap.h"
#include "foodManager.h"
#include "anthillManager.h"

class World
{
public:
	World();
	~World();

	// Update les différentes entitées en jeux
	void update();
	// Nouveau tour de jeu
	void turnUpdate();

	void draw(sf::RenderWindow& window);

	FoodManager& getFoodManager();
	TileMap& getTileMap();
	AnthillManager& getAnthillManager();

	sf::Vector2u mapSizeInPixel();

private:
	TileMap _tilemap;
	FoodManager _foodManager;
	AnthillManager _anthillManager;
};