#include "warriorAnt.h"

#include "textureManager.h"
#include "world.h"

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
		break;
	case States::harvesting:
		harvest();
		break;
	case States::goingBack:
		goBack();
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
			this->_nextDestinationTile = availableTile;
			_currentState = States::harvesting;
			return;
		}
	}
	// Si il n'y a qu'une seule possibilité, on y va
	if (availableTiles.size() == 1) {
		this->_nextDestinationTile = availableTiles[0];
		return;
	}

	sf::Vector2u lastTilePosition = sf::Vector2u(-1, -1);
	if (_pathToAnthill.size() > 1) {
		lastTilePosition = _pathToAnthill[_pathToAnthill.size() - 2];
	}

	// On mélange les tiles possibles pour randomiser les déplacements
	std::random_shuffle(availableTiles.begin(), availableTiles.end());

	// Sinon on enleve la derniere position ou on a été et on prend la premiere qui vient
	for (auto availableTile : availableTiles) {
		if (availableTile != lastTilePosition) {
			this->_nextDestinationTile = availableTile;
			return;
		}
	}
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
	if (_pathToAnthill.size() == 0) {
		anthill.dropFood(_food);
		_food = 0;
		_currentState = States::exploring;
	}
}