#include "ant.h"

#include "config.h"
#include "world.h"
#include "utils.h"
#include "anthill.h"

#include <iostream>
#include <math.h>       /* ceil */

Ant::Ant(World& world, Anthill& anthill, sf::Vector2u position) : world(world), anthill(anthill) {
	setOrigin(32, 32);
	_lastTilePosition = getTilePosition();
	_nextDestinationTile = position;
	setTilePosition(position);
}

Ant::~Ant() {
}

void Ant::update() {
	if (_nextDestinationTile != _lastTilePosition) {
		moveToDestination();
	}
}

void Ant::turnUpdate() {
}

void Ant::setTilePosition(sf::Vector2u newPos)
{
	DrawableEntity::setTilePosition(newPos);
	_lastTilePosition = newPos;
}

Ant::AntType Ant::getType()
{
	return type;
}

bool Ant::compareTypes(Ant* ant1, Ant* ant2)
{
	return ant1->getType() < ant2->getType();
}

void Ant::moveToDestination() {
	orientateToDestination();

	// 64 c'est la taille d'un tile en pixel, on enleve 1 pour aller légerement plus vite que la fin du tour et on arrondit au dessus
	float velocity = ceil(64.f / (Config::getNbrOfTickPerTurn() - 1));
	//std::cout << _lastTilePosition.x << " " << _lastTilePosition.y << "--" << _nextDestinationTile.x << " " << _nextDestinationTile.y << " v: "<< velocity <<std::endl;

	// Si la distance entre la tile et la fourmi est inférieur à la vélocité alors on peut juste la mettre dessus pour éviter les 0.... pixels
	sf::Vector2f destinationPos = sf::Vector2f(_nextDestinationTile.x * 64 + getOrigin().x, _nextDestinationTile.y * 64 + getOrigin().y);

	if (Utils::distance(destinationPos, getPosition()) <= velocity) {
		_lastTilePosition = _nextDestinationTile;
		setPosition(destinationPos);
		return;
	}
	
	int dx = 0, dy = 0;
	// Vers la droite
	if (_nextDestinationTile.x > _lastTilePosition.x) {
		dx = 1;
	}
	// Vers la gauche
	else if (_nextDestinationTile.x < _lastTilePosition.x) {
		dx = -1;
	}
	// Vers le haut
	if (_nextDestinationTile.y < _lastTilePosition.y) {
		dy = -1;
	}
	// Vers le bas
	else if (_nextDestinationTile.y > _lastTilePosition.y) {
		dy = 1;
	}

	move(sf::Vector2f(velocity * dx, velocity * dy));
}

void Ant::orientateToDestination() {
	// Vers la droite
	if (_nextDestinationTile.x > _lastTilePosition.x) {
		setRotation(90.f);
	}
	// Vers la gauche
	else if (_nextDestinationTile.x < _lastTilePosition.x) {
		setRotation(270.f);
	}
	// Vers le haut
	if (_nextDestinationTile.y < _lastTilePosition.y) {
		setRotation(0.f);
	}
	// Vers le bas
	else if (_nextDestinationTile.y > _lastTilePosition.y) {
		setRotation(180.f);
	}
}