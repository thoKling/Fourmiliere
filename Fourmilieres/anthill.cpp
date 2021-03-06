#include "anthill.h"

#include "world.h"
#include "utils.h"
#include "hud.h"

#include "warriorAnt.h"
#include "workerAnt.h"
#include "queenAnt.h"

#include <iostream>
#include <string>

Anthill::Anthill(World& world, int maxFood, int maxAnts, std::vector<sf::Vector2u> tiles, int evaporationRate) :
	_world(world), 
	_maxFood(maxFood), 
	_maxAnts(maxAnts), 
	_pheromonesManager(world.getTileMap().getMapSize(), evaporationRate),
	_tiles(tiles)
{
	WarriorAnt* wa = new WarriorAnt(world, *this, sf::Vector2u(20, 20));
	_antList.push_back(wa);

	WarriorAnt* wa2 = new WarriorAnt(world, *this, sf::Vector2u(21, 20));
	_antList.push_back(wa2);

	WorkerAnt* woa = new WorkerAnt(world, *this, sf::Vector2u(20, 20));
	_antList.push_back(woa);

	QueenAnt* queen = new QueenAnt(world, *this, sf::Vector2u(20, 20));
	_antList.push_back(queen);

	_food = 50;
}

Anthill::~Anthill() {
	for (auto ant : _antList) {
		delete(ant);
	}
}

void Anthill::draw(sf::RenderWindow& window) {
	// On trie par type pour avoir les plus importantes dessin?es par dessus les autres (voir Ant::AntType)
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
	_pheromonesManager.turnUpdate();
	// On copie la liste, on aura des probl?mes d'it?rateur sinon si une reine pond des oeufs pendant le tour ou qu'un oeuf ?volue
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
			foodToBeConsumed += 1;
			break;
		}
	}
	_food -= foodToBeConsumed;
	
	if (_food < 0) {
		std::cout << "perdu" << std::endl;
	}

	Hud::getInstance().setAntNb(Utils::to_str(_antList.size()) + "/" + Utils::to_str(_maxAnts));
	Hud::getInstance().setFoodNb(Utils::to_str(_food) + "/" + Utils::to_str(_maxFood));
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

bool Anthill::isFullOfAnts()
{
	return _antList.size() == _maxAnts;
}

void Anthill::dropFood(int food) {
	_food += food;

	if (_food > _maxFood)
		_food = _maxFood;
}

bool Anthill::isOnAnthill(sf::Vector2u position)
{
	return Utils::contains(_tiles, position);
}

PheromonesManager& Anthill::getPheromonesManager()
{
	return _pheromonesManager;
}
