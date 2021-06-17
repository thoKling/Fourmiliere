#pragma once
#include <SFML/Graphics.hpp>
#include "gamestate.h"
#include "world.h"
#include "camera.h"

class game : public GameState
{
public:
	game();
	~game();
	virtual void update();
	virtual void handleInputs(const sf::Vector2i& mousePixelPos, const sf::Vector2f& mousePos, const sf::Event& event);
	virtual void manageDraw(sf::RenderWindow& window);

private:
	int _currentTick = 0;

	World _world;
	Camera _camera;
};