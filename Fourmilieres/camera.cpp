#include "camera.h"
#include "utils.h"
#include "application.h"

Camera::Camera()
{
	sf::RenderWindow& window = Application::getWindow();
	_currentView = window.getDefaultView();
	_currentView.zoom(2.0f);
	_currentView.setCenter(window.getSize().x, window.getSize().y);

	_velocity = 7;
}

Camera::~Camera()
{
}

void Camera::handleInputs() 
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_dIsHeld = false;

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		_qIsHeld = false;

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_sIsHeld = false;

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		_upIsHeld = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_dIsHeld = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		_qIsHeld = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_sIsHeld = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		_upIsHeld = true;
}

void Camera::update(sf::Vector2u mapSize)
{
	moveCamera(mapSize);
}
sf::View Camera::getView()
{
	return _currentView;
}
void Camera::moveCamera(sf::Vector2u mapSize)
{
	double x = 0, y = 0;
	sf::RenderWindow& window = Application::getWindow();

	if (_dIsHeld && _currentView.getCenter().x < mapSize.x - window.getSize().x)
	{
		x += _velocity;
	}
	if (_qIsHeld && _currentView.getCenter().x > window.getSize().x)
	{
		x += -_velocity;
	}

	if (_sIsHeld && _currentView.getCenter().y < mapSize.y - window.getSize().y)
	{
		y += _velocity;
	}

	if (_upIsHeld && _currentView.getCenter().y > window.getSize().y)
	{
		y += -_velocity;
	}

	// Pour ne pas avoir de déplacement plus rapide en diagonale
	sf::Vector2f unitVec = Utils::getVecUnit(sf::Vector2f(0, 0), sf::Vector2f(x, y));
	x *= std::abs(unitVec.x);
	y *= std::abs(unitVec.y);

	// Déplacement
	_currentView.move(x, y);
}