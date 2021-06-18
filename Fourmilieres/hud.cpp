#include "hud.h"

#include "config.h"

Hud Hud::_instance = Hud();

Hud & Hud::getInstance()
{
	return _instance;
}

Hud::Hud() {
	_baseRect.setPosition(2,1);
	_baseRect.setSize(sf::Vector2f(WINDOWS_WIDTH - 4, 50));
	_baseRect.setFillColor(sf::Color::White);
	_baseRect.setOutlineThickness(2.f);
	_baseRect.setOutlineColor(sf::Color::Black);

	if (!_font.loadFromFile("Ressources/comicz.ttf"))
		throw std::string("Impossible de charger la police d'écriture");

	_antsNb.setFont(_font);
	_antsNb.setCharacterSize(18);
	_antsNb.setPosition(10, 5);
	_antsNb.setFillColor(sf::Color::Black);

	_foodNb.setFont(_font);
	_foodNb.setCharacterSize(18);
	_foodNb.setPosition(200, 5);
	_foodNb.setFillColor(sf::Color::Black);
}

Hud::~Hud()
{
}

void Hud::setAntNb(std::string str)
{
	_antsNb.setString(str);
}

void Hud::setFoodNb(std::string str)
{
	_foodNb.setString(str);
}

void Hud::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// on applique la transformation
	states.transform *= getTransform();

	// et on dessine enfin le tableau de vertex
	target.draw(_baseRect, states);
	target.draw(_antsNb, states);
	target.draw(_foodNb, states);
}

