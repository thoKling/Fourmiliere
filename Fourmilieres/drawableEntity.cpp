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
	// on applique la transformation de l'entité -- on la combine avec celle qui a été passée par l'appelant
	states.transform *= getTransform(); // getTransform() est définie par sf::Transformable

	// on dessine le sprite
	target.draw(_sprite, states);
}