#include "workerAnt.h"

#include "world.h"
#include "textureManager.h"

#include "warriorAnt.h"

WorkerAnt::WorkerAnt(World& world, Anthill& anthill, sf::Vector2u position) : Ant(world, anthill, position) {
	_sprite.setTexture(*TextureManager::loadText("Ressources/worker_ant.png"));
	type = Ant::AntType::Worker;
}

WorkerAnt::~WorkerAnt() {

}

void WorkerAnt::turnUpdate() {
	Ant::turnUpdate();
	move();
	if (turnNb == 4) {
		evolve();
	}
	turnNb++;
}

void WorkerAnt::move() {
	sf::Vector2u currentTilePos = getTilePosition();
	// On récupere les tiles adjacentes
	std::vector<sf::Vector2u> availableTiles;
	std::vector<sf::Vector2u> adjacentTiles;
	adjacentTiles.push_back(sf::Vector2u(currentTilePos.x + 1, currentTilePos.y));
	adjacentTiles.push_back(sf::Vector2u(currentTilePos.x - 1, currentTilePos.y));
	adjacentTiles.push_back(sf::Vector2u(currentTilePos.x, currentTilePos.y + 1));
	adjacentTiles.push_back(sf::Vector2u(currentTilePos.x, currentTilePos.y - 1));

	// On recupere les tiles adjacent ou on est toujours dans la fourmiliere
	for (auto adjacentTile : adjacentTiles) {
		if (world.getTileMap().isAnthill(adjacentTile)) {
			availableTiles.push_back(adjacentTile);
		}
	}

	// On mélange les tiles possibles pour randomiser les déplacements
	std::random_shuffle(availableTiles.begin(), availableTiles.end());

	// Sinon on enleve la derniere position ou on a été et on prend la premiere qui vient
	this->_nextDestinationTile = availableTiles[0];
}

void WorkerAnt::evolve() {
	anthill.removeAnt(this);

	WarriorAnt* warrior = new WarriorAnt(world, anthill, getTilePosition());

	anthill.addAnt(warrior);
}