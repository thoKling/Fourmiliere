#pragma once

#include <SFML/Graphics.hpp>

///
/// Singleton qui sert à afficher les infos
///
class Hud : public sf::Drawable, public sf::Transformable {
public:
	static Hud& getInstance();

	~Hud();

	void setAntNb(std::string str);
	void setFoodNb(std::string str);

private:
	Hud();
	static Hud _instance;

	sf::RectangleShape _baseRect;
	sf::Font _font;

	sf::Text _antsNb;
	sf::Text _foodNb;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};