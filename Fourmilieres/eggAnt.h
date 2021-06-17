#pragma once

#include "ant.h"

class EggAnt : public Ant
{
public:
	EggAnt(World& world, Anthill& anthill, sf::Vector2u position);
	~EggAnt();

	virtual void turnUpdate();
private:
	void evolve();

	int turnNb = 0; // Compte les tours pour savoir quand évoluer
};

