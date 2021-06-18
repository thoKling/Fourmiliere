#include "warriorAnt.h"

#include "textureManager.h"
#include "world.h"
#include "utils.h"

#include <algorithm>

#include <iostream>

WarriorAnt::WarriorAnt(World& world, Anthill& anthill, sf::Vector2u position): Ant(world, anthill, position)
{
	_sprite.setTexture(*TextureManager::loadText("Ressources/warrior_ant.png"));
	_currentState = States::exploring;
	_food = 0;
	type = Ant::AntType::Warrior;
}


WarriorAnt::~WarriorAnt()
{
}

void WarriorAnt::turnUpdate() {
	Ant::turnUpdate();
	switch (_currentState) {
	case States::exploring:
		explore();
		//anthill.getPheromonesManager().setPheromones(_nextDestinationTile, 50);
		break;
	case States::harvesting:
		harvest();
		break;
	case States::goingBack:
		goBack();
		anthill.getPheromonesManager().setPheromones(_nextDestinationTile, 90);
		break;
	}
}

void WarriorAnt::explore() {
	sf::Vector2u currentTilePos = getTilePosition();
	// On ajoute la position courante au chemin
	_pathToAnthill.push_back(getTilePosition());
	std::vector<sf::Vector2u> availableTiles;
	std::vector<sf::Vector2u> adjacentTiles;
	adjacentTiles.push_back(sf::Vector2u(currentTilePos.x + 1, currentTilePos.y));
	adjacentTiles.push_back(sf::Vector2u(currentTilePos.x - 1, currentTilePos.y));
	adjacentTiles.push_back(sf::Vector2u(currentTilePos.x, currentTilePos.y + 1));
	adjacentTiles.push_back(sf::Vector2u(currentTilePos.x, currentTilePos.y - 1));
	// On recupere les tiles adjacent ou il n'y a pas d'obstacles
	for (auto adjacentTile : adjacentTiles) {
		if (!world.getTileMap().isObstacle(adjacentTile)) {
			availableTiles.push_back(adjacentTile);
		}
	}
	// On regarde si il y a de la nourriture sur l'une d'entre elle
	for (auto availableTile : availableTiles) {
		if (world.getFoodManager().isFoodThere(availableTile)) {
			_nextDestinationTile = availableTile;
			_currentState = States::harvesting;
			return;
		}
	}
	// Si il n'y a qu'une seule possibilité, on y va
	if (availableTiles.size() == 1) {
		_nextDestinationTile = availableTiles[0];
		return;
	}

	sf::Vector2u lastTilePosition = sf::Vector2u(-1, -1);
	if (_pathToAnthill.size() > 1) {
		lastTilePosition = _pathToAnthill[_pathToAnthill.size() - 2];
	}

	// On enlève la dernière tile ou on a été
	auto newAvailableTiles = std::vector<sf::Vector2u>();
	for (auto availableTile : availableTiles) {
		if (availableTile != lastTilePosition) {
			newAvailableTiles.push_back(availableTile);
		}
	}
	availableTiles = newAvailableTiles;
	
	// On cherche les pheromones
	auto availableTilesTemp = availableTiles;
	for (int i = 0; i < availableTiles.size(); i++) {
		// On cherche le max
		int maxPheromones = 0;
		sf::Vector2u maxPosition = sf::Vector2u(0, 0);
		for (auto availableTile : availableTilesTemp) {
			int pheromonesLevel = anthill.getPheromonesManager().getPheromones(availableTile);
			if (maxPheromones < pheromonesLevel) {
				maxPheromones = pheromonesLevel;
				maxPosition = availableTile;
			}
		}
		// Si on a pas trouvé de pheromones
		if (maxPheromones == 0) {
			break;
		}
		// On test le maximum qu'on a trouvé
		int randInt = rand() % 100;
		// Si le rand est bon, on va sur cette tile
		if (randInt < maxPheromones) {
			_nextDestinationTile = maxPosition;
			return;
		}
		// Sinon on enleve la position et on recommence
		else {
			auto newAvailableTiles = std::vector<sf::Vector2u>();
			for (auto availableTile : availableTilesTemp) {
				if (availableTile != maxPosition) {
					newAvailableTiles.push_back(availableTile);
				}
			}
			availableTilesTemp = newAvailableTiles;
		}
	}

	// On mélange les tiles possibles pour randomiser les déplacements
	std::random_shuffle(availableTiles.begin(), availableTiles.end());

	// Sinon On prend la premiere qui vient
	_nextDestinationTile = availableTiles[0];
}

void WarriorAnt::harvest() {
	if (!world.getFoodManager().isFoodThere(getTilePosition())) {
		_currentState = States::exploring;
		return;
	}

	_food = world.getFoodManager().harvest(getTilePosition());

	_currentState = States::goingBack;
}

void WarriorAnt::goBack() {
	_nextDestinationTile = _pathToAnthill.back();
	_pathToAnthill.pop_back();
	if (_pathToAnthill.size() == 0 || anthill.isOnAnthill(_nextDestinationTile)) {
		anthill.dropFood(_food);
		_pathToAnthill.clear();
		_food = 0;
		_currentState = States::exploring;
	}
}