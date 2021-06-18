#include "foodManager.h"
#include "tilemap.h"

#include <iostream>

FoodManager::FoodManager() {
	
}

FoodManager::~FoodManager() {
	for (auto food : _foodList) {
		delete(food);
	}
}

void FoodManager::update() 
{
	for (auto food : _foodList) {
		food->update();
	}
}

void FoodManager::draw(sf::RenderWindow& window) 
{
	for (auto food : _foodList) {
		window.draw(*food);
	}
}

void FoodManager::generateFood(unsigned int numberOfFood, TileMap& tileMap) 
{
	sf::Vector2u mapSize = tileMap.getMapSize();
	for (int i = 0; i < numberOfFood; i++) {
		bool found = false;
		while (!found) {
			unsigned int randX = rand() % mapSize.x;
			unsigned int randY = rand() % mapSize.y;
			// On vérifie qu'on est pas sur un obstacle et qu'il n'y a pas déjà de la nourriture ici
			if (!tileMap.isObstacle(sf::Vector2u(randX, randY)) && ! isFoodThere(sf::Vector2u(randX, randY))) {
				Food* newFood = new Food();
				newFood->setPosition((randX * 64), (randY * 64));
				_foodList.push_back(newFood);
				found = true;
			}
		}
	}
}
void FoodManager::removeFood(sf::Vector2u position) {
	//std::cout << "Remove food" << position.x << " " << position.y << std::endl;
	int index = -1;
	for (int i = 0; i < _foodList.size(); i++) {
		if (_foodList[i]->getTilePosition() == position) {
			index = i;
		}
	}
	if (index != -1) {
		_foodList.erase(_foodList.begin() + index);
	}
}

int FoodManager::harvest(sf::Vector2u position)
{
	int res = 0;
	for (auto food : _foodList) {
		if (food->getTilePosition() == position) {
			res = food->harvest();
			if (food->getFoodLeft() <= 0) {
				removeFood(position);
			}
			break;
		}
	}
	return res;
}

bool FoodManager::isFoodThere(sf::Vector2u position) {
	for (auto food : _foodList) {
		if (food->getTilePosition().x == position.x && food->getTilePosition().y == position.y) {
			return true;
		}
	}
	return false;
}