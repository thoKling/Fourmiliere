#pragma once

#include "ant.h"

class WorkerAnt : public Ant
{
public:
	WorkerAnt(World& world, Anthill& anthill, sf::Vector2u position);
	~WorkerAnt();

	virtual void turnUpdate();

protected:
	void move();

private:
	void evolve();

	int turnNb = 0;
};

