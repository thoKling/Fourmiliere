#pragma once

#include "ant.h"

class WarriorAnt : public Ant
{
public:
	WarriorAnt(World& world, Anthill& anthill, sf::Vector2u position);
	~WarriorAnt();

	virtual void turnUpdate();

private:
	enum States {
		exploring,
		harvesting,
		goingBack
	};

	States _currentState;

	void explore();
	void harvest();
	void goBack();

	int _food;

	std::vector<sf::Vector2u> _pathToAnthill; // Chemin pour aller a la fourmiliere quand on est en mode exploration
};

