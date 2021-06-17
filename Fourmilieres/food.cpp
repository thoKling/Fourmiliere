#include "food.h"
#include "textureManager.h"
#include "utils.h"

Food::Food() {
	_foodLeft = 500;

	_sprite.setTexture(*TextureManager::loadText("Ressources/apple.png"));
}
Food::~Food() {

}

void Food::update() {

}

int Food::getFoodLeft() {
	return _foodLeft;
}

int Food::harvest() {
	if (_foodLeft > 5) {
		_foodLeft = _foodLeft - 5;
		return 5;
	}
	else {
		return _foodLeft;
	}
}