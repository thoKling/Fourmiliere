#include "pheromonesManager.h"



PheromonesManager::PheromonesManager(sf::Vector2u mapSize, int evaporationRate) : _evaporationRate(evaporationRate)
{
	_pheromones = std::vector<std::vector<int>>(mapSize.x, std::vector<int>(mapSize.y, 0));

}


PheromonesManager::~PheromonesManager()
{
}

void PheromonesManager::setPheromones(sf::Vector2u position, int level)
{
	if (_pheromones[position.x][position.y] < level) {
		_pheromones[position.x][position.y] = level;
	}
}

int PheromonesManager::getPheromones(sf::Vector2u position)
{
	return _pheromones[position.x][position.y];
}

void PheromonesManager::turnUpdate()
{
	for (int i = 0; i < _pheromones.size(); i++) {
		for (int j = 0; j < _pheromones[0].size(); j++) {
			if (_pheromones[i][j] > 0) {
				_pheromones[i][j] -= _evaporationRate;
			}
		}
	}
}
