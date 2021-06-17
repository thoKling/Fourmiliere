#pragma once

#include "workerAnt.h"

///
/// On hérite de worker ant pour que la reine bouge dans la fourmiliere de la meme facon
///
class QueenAnt : public WorkerAnt
{
public:
	QueenAnt(World& world, Anthill& anthill, sf::Vector2u position);
	~QueenAnt();

	virtual void turnUpdate();

private:
	void layEgg();
};

