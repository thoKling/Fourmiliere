#include "food.h"
#include "textureManager.h"
#include "utils.h"

Food::Food() {
	_foodLeft = 300;

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
	if (_foodLeft > 15) {
		_foodLeft -= 15;
		return 15;
	}
	else {
		_foodLeft = 0;
		return _foodLeft;
	}
}