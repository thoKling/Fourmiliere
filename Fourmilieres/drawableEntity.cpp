#include "drawableEntity.h"

DrawableEntity::DrawableEntity()
{
}


DrawableEntity::~DrawableEntity()
{

}

sf::Vector2u DrawableEntity::getTilePosition() {
	return sf::Vector2u(getPosition().x / 64, getPosition().y / 64);
}

void DrawableEntity::setTilePosition(sf::Vector2u newPos) {
	setPosition(newPos.x * 64, newPos.y * 64);
}

void DrawableEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// on applique la transformation de l'entit� -- on la combine avec celle qui a �t� pass�e par l'appelant
	states.transform *= getTransform(); // getTransform() est d�finie par sf::Transformable

	// on dessine le sprite
	target.draw(_sprite, states);
}