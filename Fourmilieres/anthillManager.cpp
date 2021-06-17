#include "anthillManager.h"
#include "tilemap.h"
#include "foodManager.h"

#include "world.h"

AnthillManager::AnthillManager() {

}
AnthillManager::~AnthillManager() {
	for (auto anthill : _anthillList) {
		delete(anthill);
	}
}

void AnthillManager::update()
{
	for (auto anthill : _anthillList) {
		anthill->update();
	}
}

void AnthillManager::turnUpdate() {
	for (auto anthill : _anthillList) {
		anthill->turnUpdate();
	}
}

void AnthillManager::draw(sf::RenderWindow& window) {
	for (auto anthill : _anthillList) {
		anthill->draw(window);
	}
}

void AnthillManager::createAnthill(World& world, sf::Vector2u position) 
{
	// On nettoie la map dans la zone de la fourmiliere et on met la fourmiliere
	/// ######
	/// ##FF##
	/// #FFFF#   == \ Notre fourmiliere trop cool
	/// #FFFF#   == / Notre fourmiliere trop cool
	/// ##FF##
	/// ######
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 6; j++) {
			sf::Vector2u currentPosition = sf::Vector2u(position.x - 2 + i, position.y - 2 + j);
			world.getFoodManager().removeFood(currentPosition);
			if (
				// Nettoyage de la zone autour sur 1 tile
				(i == 0 || j == 0 || i == 5 || j == 5) 
				||
				// Les coins de la fourmiliere
				(i == 1 && j == 1) || (i == 1 && j == 4) || (i == 4 && j == 1) || (i == 4 && j == 4)
				) {
				world.getTileMap().changeTile(currentPosition, 0);
			}
			else {
				world.getTileMap().changeTile(currentPosition, 2);
			}
		}
	}
	_anthillList.push_back(new Anthill(world, 200, 50));
}