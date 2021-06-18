#include "game.h"

#include <string>
#include <iostream>

#include "application.h"
#include "config.h"

game::game(sf::Vector2u mapSize, int obstaclesNbr, int foodNbr, int evaporationRate) :
	_world(mapSize, obstaclesNbr, foodNbr, evaporationRate)
{
}

game::~game()
{
}

void game::update()
{
	if (_currentTick % Config::getNbrOfTickPerTurn() == 0) {
		_currentTick = 1;
		_world.turnUpdate();
		//std::cout << "Nouveau tour" << std::endl;
	}
	_currentTick++;

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