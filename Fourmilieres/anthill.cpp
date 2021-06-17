#include "anthill.h"
#include "warriorAnt.h"
#include "workerAnt.h"
#include "queenAnt.h"

#include <iostream>

Anthill::Anthill(World& world, int maxFood, int maxAnts): _world(world), _maxFood(maxFood), _maxAnts(maxAnts) {
	WarriorAnt* wa = new WarriorAnt(world, *this, sf::Vector2u(20, 20));
	_antList.push_back(wa);

	WarriorAnt* wa2 = new WarriorAnt(world, *this, sf::Vector2u(21, 20));
	_antList.push_back(wa2);

	WorkerAnt* woa = new WorkerAnt(world, *this, sf::Vector2u(20, 20));
	_antList.push_back(woa);

	QueenAnt* queen = new QueenAnt(world, *this, sf::Vector2u(20, 20));
	_antList.push_back(queen);

	_food = 50;

	for (auto ant : _antList) {
		std::cout << ant->getPosition().x << " " << ant->getPosition().y;
	}
}

Anthill::~Anthill() {
	for (auto ant : _antList) {
		delete(ant);
	}
}

void Anthill::draw(sf::RenderWindow& window) {
	// On trie par type pour avoir les plus importantes dessinées par dessus les autres (voir Ant::AntType)
	auto sortedAnt = _antList;
	std::sort(sortedAnt.begin(), sortedAnt.end(), Ant::compareTypes);
	for (auto ant : sortedAnt) {
		window.draw(*ant);
	}
}

void Anthill::update() {
	for (auto ant : _antList) {
		ant->update();
	}
}

void Anthill::turnUpdate() {
	float foodToBeConsumed = 0;
	// On copie la liste, on aura des problèmes d'itérateur sinon si une reine pond des oeufs pendant le tour ou qu'un oeuf évolue
	auto antCopyList = _antList;
	for (auto ant : antCopyList) {
		ant->turnUpdate();
		switch (ant->getType()) {
		case Ant::AntType::Worker:
			foodToBeConsumed += 0.25;
			break;
		case Ant::AntType::Warrior:
			foodToBeConsumed += 0.5;
			break;
		case Ant::AntType::Queen:
			foodToBeConsumed += 2;
			break;
		}
	}
	_food -= foodToBeConsumed;
	if (_food < 0) {
		std::cout << "perdu" << std::endl;
	}
	std::cout << _food;
}

void Anthill::addAnt(Ant* newAnt) {
	_antList.push_back(newAnt);
}
void Anthill::removeAnt(Ant* ant) {
	auto res = std::vector<Ant*>();
	for (auto t_ant : _antList) {
		if (t_ant != ant) {
			res.push_back(t_ant);
		}
	}
	_antList = res;
}

void Anthill::dropFood(int food) {
	_food += food;

	if (food > _maxFood)
		food = _maxFood;
}