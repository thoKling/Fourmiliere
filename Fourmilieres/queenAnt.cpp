#include "queenAnt.h"

#include "textureManager.h"
#include "world.h"

#include "eggAnt.h"


QueenAnt::QueenAnt(World& world, Anthill& anthill, sf::Vector2u position) : WorkerAnt(world, anthill, position)
{
	_sprite.setTexture(*TextureManager::loadText("Ressources/queen_ant.png"));
	type = Ant::AntType::Queen;
}


QueenAnt::~QueenAnt()
{
}

void QueenAnt::turnUpdate() {
	WorkerAnt::move(); // On bouge de facon aléatoire dans la fourmiliere
	int randNb = rand() % 100;
	if (randNb < 8) {
		layEgg();
	}
}

// Créer un oeuf à la position actuelle 
void QueenAnt::layEgg() {
	EggAnt* newEgg = new EggAnt(world, anthill, getTilePosition());
	this->anthill.addAnt(newEgg);
}