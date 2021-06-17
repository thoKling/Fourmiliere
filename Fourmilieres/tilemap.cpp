#include "TileMap.h"

#include <iostream>

TileMap::TileMap() : _tileSize(sf::Vector2u(64, 64))
{
	// on charge la texture du tileset
	if (!_tileset.loadFromFile("Ressources/tileset.png"))
		throw std::string("Impossible de charger le tileset");

}
TileMap::~TileMap()
{
}

void TileMap::generateMap(const sf::Vector2u size, const int obstaclesNbr, const int foodNbr)
{
	_tiles = std::vector<std::vector<int>>(size.x, std::vector<int>(size.y, 0));
	for (int i = 0; i < size.x; i++) {
		for (int j = 0; j < size.y; j++) {
			// On ajoute des bordures sur les coins
			if (i == 0 || i == size.x - 1 || j == 0 || j == size.y - 1) {
				_tiles[i][j] = 1;
			}
		}
	}
	randomizeTile(obstaclesNbr, 1);
	loadAllTiles();
}

void TileMap::loadAllTiles() 
{
	unsigned int width = _tiles[0].size();
	unsigned int height = _tiles.size();

	// on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
	_vertices.setPrimitiveType(sf::Quads);
	_vertices.resize(width * height * 4);

	// on remplit le tableau de vertex, avec un quad par tuile
	for (unsigned int i = 0; i < width; ++i)
	{
		for (unsigned int j = 0; j < height; ++j)
		{
			loadTile(sf::Vector2u(i, j));
		}
	}
}

void TileMap::randomizeTile(int nbr, int tileNbr) {
	for (int i = 0; i < nbr; i++) {
		bool found = false;
		while (!found) {
			int randX = rand() % _tiles[0].size();
			int randY = rand() % _tiles.size();
			if (_tiles[randX][randY] != 1) {
				_tiles[randX][randY] = 1;
				found = true;
			}
		}
	}
}

sf::Vector2u TileMap::getMapSize()
{
	return sf::Vector2u(_tiles[0].size(), _tiles.size());
}

bool TileMap::isObstacle(sf::Vector2u position) {
	return _tiles[position.x][position.y] == 1;
}

bool TileMap::isAnthill(sf::Vector2u position) {
	return _tiles[position.x][position.y] == 2;
}

void TileMap::changeTile(sf::Vector2u position, int tileNumber)
{
	_tiles[position.x][position.y] = tileNumber;
	loadTile(position);
}

void TileMap::loadTile(sf::Vector2u position) 
{
	int i = position.x;
	int j = position.y;
	// on récupère le numéro de tuile courant
	int tileNumber = _tiles[i][j];

	// on en déduit sa position dans la texture du tileset
	int tu = tileNumber % (_tileset.getSize().x / _tileSize.x);
	int tv = tileNumber / (_tileset.getSize().x / _tileSize.x);

	// on récupère un pointeur vers le quad à définir dans le tableau de vertex
	sf::Vertex* quad = &_vertices[(i + j * _tiles[0].size()) * 4];

	// on définit ses quatre coins
	quad[0].position = sf::Vector2f(i * _tileSize.x, j * _tileSize.y);
	quad[1].position = sf::Vector2f((i + 1) * _tileSize.x, j * _tileSize.y);
	quad[2].position = sf::Vector2f((i + 1) * _tileSize.x, (j + 1) * _tileSize.y);
	quad[3].position = sf::Vector2f(i * _tileSize.x, (j + 1) * _tileSize.y);

	// on définit ses quatre coordonnées de texture
	quad[0].texCoords = sf::Vector2f(tu * _tileSize.x, tv * _tileSize.y);
	quad[1].texCoords = sf::Vector2f((tu + 1) * _tileSize.x, tv * _tileSize.y);
	quad[2].texCoords = sf::Vector2f((tu + 1) * _tileSize.x, (tv + 1) * _tileSize.y);
	quad[3].texCoords = sf::Vector2f(tu * _tileSize.x, (tv + 1) * _tileSize.y);
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// on applique la transformation
	states.transform *= getTransform();

	// on applique la texture du tileset
	states.texture = &_tileset;

	// et on dessine enfin le tableau de vertex
	target.draw(_vertices, states);
}