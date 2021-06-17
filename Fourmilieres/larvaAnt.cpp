#include "larvaAnt.h"

#include "anthill.h"
#include "textureManager.h"

LarvaAnt::LarvaAnt(World& world, Anthill& anthill, sf::Vector2u position) : WorkerAnt(world, anthill, position)
{
	_sprite.setTexture(*TextureManager::loadText("Ressources/larva.png"));
	type = Ant::AntType::Larva;
}


LarvaAnt::~LarvaAnt()
{
}

void LarvaAnt::turnUpdate()
{
	if (turnNb == 2) {
		WorkerAnt::turnUpdate();
	}
	else if (turnNb == 4) {
		evolve();
	}
	turnNb++;
}

void LarvaAnt::evolve() {
	anthill.removeAnt(this);

	WorkerAnt* woa = new WorkerAnt(world, anthill, getTilePosition());

	anthill.addAnt(woa);
}