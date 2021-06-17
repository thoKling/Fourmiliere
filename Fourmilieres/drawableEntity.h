#pragma once

#include <SFML/Graphics.hpp>

class DrawableEntity : public sf::Drawable, public sf::Transformable
{
public:
	DrawableEntity();
	~DrawableEntity();

	sf::Vector2u getTilePosition(); // Renvoie la position en nombre de tile
	void setTilePosition(sf::Vector2u);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Sprite _sprite;
};