#pragma once

#include "ant.h"

#include <SFML/Window.hpp>

#include "pheromonesManager.h"

class Anthill
{
public:
	Anthill(World& world, int maxFood, int maxAnts, std::vector<sf::Vector2u> tiles, int evaporationRate);
	~Anthill();

	void update();
	void turnUpdate();

	void draw(sf::RenderWindow& window);
	void dropFood(int food);

	bool isOnAnthill(sf::Vector2u position);

	PheromonesManager& getPheromonesManager();

	// La fourmiliere s'occupera de la destruction du pointeur
	void addAnt(Ant* newAnt);
	void removeAnt(Ant* ant);

private:
	World& _world;
	PheromonesManager _pheromonesManager;

	float _food;
	int _maxFood;
	int _maxAnts; // Nombre maximum de fourmis dans la fourmiliere

	std::vector<sf::Vector2u> _tiles; // Tiles ou se trouve la fourmiliere

	std::vector<Ant*> _antList;
};