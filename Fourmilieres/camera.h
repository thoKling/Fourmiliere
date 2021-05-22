#pragma once
#include <SFML/Graphics.hpp>
#include "tilemap.h"

class Camera
{
public:
	Camera();
	~Camera();

	void handleInputs();
	void update(sf::Vector2u mapSize);

	sf::View getView();

private:
	sf::View _currentView;

	void moveCamera(sf::Vector2u mapSize);

	/* Les "interrupteurs de d�placement".
		True: les d�placements ont lieu,
		False: il n'y a pas de d�placements 
		*/
	bool _dIsHeld = false;
	bool _qIsHeld = false;
	bool _sIsHeld = false;
	bool _upIsHeld = false;

	int _velocity;
};