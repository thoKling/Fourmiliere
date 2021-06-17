#pragma once

#include "ant.h"

#include <SFML/Window.hpp>

class Anthill
{
public:
	Anthill(World& world, int maxFood, int maxAnts);
	~Anthill();

	void update();
	void turnUpdate();

	void draw(sf::RenderWindow& window);
	void dropFood(int food);
	// La fourmiliere s'occupera de la destruction du pointeur
	void addAnt(Ant* newAnt);
	void removeAnt(Ant* ant);

private:
	World& _world;
	float _food;
	int _maxFood;
	int _maxAnts; // Nombre maximum de fourmis dans la fourmiliere

	std::vector<Ant*> _antList;
};