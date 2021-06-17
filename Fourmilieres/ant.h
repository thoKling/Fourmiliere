#pragma once

#include "drawableEntity.h"

class World;
class Anthill;
class Ant : public DrawableEntity
{
public:
	///
	/// L'ordre est important, ce sera l'ordre de dessin
	///
	enum AntType {
		Egg,
		Larva,
		Worker,
		Warrior,
		Queen
	};

	Ant(World& world, Anthill& anthill, sf::Vector2u position);
	~Ant();

	// Cette fonction d'update est executée à chaque frame, on s'en sert pour gérer les animations
	virtual void update();
	// Cette fonction turn update sera éxécuté à chaque début de tour
	virtual void turnUpdate();

	virtual void setTilePosition(sf::Vector2u newPos);

	AntType getType();

	static bool compareTypes(Ant* ant1, Ant* ant2);

protected:
	World& world;
	Anthill& anthill;

	AntType type;

	sf::Vector2u _nextDestinationTile; // Tile sur laquelle on souhaite aller actuellement

	void moveToDestination();
	void orientateToDestination();

private:
	sf::Vector2u _lastTilePosition; // Derniere Tile ou on était
};