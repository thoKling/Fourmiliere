#include "eggAnt.h"

#include "larvaAnt.h"
#include "anthill.h"

#include "textureManager.h"

EggAnt::EggAnt(World& world, Anthill& anthill, sf::Vector2u position) : Ant(world, anthill, position)
{
	_sprite.setTexture(*TextureManager::loadText("Ressources/egg.png"));
	type = Ant::AntType::Egg;
}


EggAnt::~EggAnt()
{
}

void EggAnt::turnUpdate() {
	if (turnNb == 4) {
		evolve();
	}
	turnNb++;
}

void EggAnt::evolve() {
	anthill.removeAnt(this);

	LarvaAnt* larva = new LarvaAnt(world, anthill, getTilePosition());

	anthill.addAnt(larva);
}