#include "game.h"

#include <string>
#include <iostream>

#include "application.h"

game::game()
{
}

game::~game()
{
}

void game::update()
{
	_world.update();
	_camera.update(_world.mapSizeInPixel());
}

void game::handleInputs(const sf::Vector2i& mousePixelPos, const sf::Vector2f& mousePos, const sf::Event& event)
{
	_camera.handleInputs();
}

void game::manageDraw(sf::RenderWindow& window)
{
	window.setView(_camera.getView());

	_world.draw(window);
}