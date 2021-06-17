#pragma once

#include "workerAnt.h"

class LarvaAnt : public WorkerAnt
{
public:
	LarvaAnt(World& world, Anthill& anthill, sf::Vector2u position);
	~LarvaAnt();

	virtual void turnUpdate();
private: 
	int turnNb = 0;

	void evolve();
};

