#include "TileMap.h"

#include <iostream>

TileMap::TileMap()
{
}
TileMap::~TileMap()
{
}

void TileMap::load(const std::string& tileset, sf::Vector2u tileSize) 
{
	unsigned int width = _tiles[0].size();
	unsigned int height = _tiles.size();

	// on charge la texture du tileset
	if (!_tileset.loadFromFile(tileset))
		throw std::string("Impossible de charger le tileset");

	// on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
	_vertices.setPrimitiveType(sf::Quads);
	_vertices.resize(width * height * 4);

	// on remplit le tableau de vertex, avec un quad par tuile
	for (unsigned int i = 0; i < width; ++i)
	{
		for (unsigned int j = 0; j < height; ++j)
		{
			// on récupère le numéro de tuile courant
			int tileNumber = _tiles[j][i];

			// on en déduit sa position dans la texture du tileset
			int tu = tileNumber % (_tileset.getSize().x / tileSize.x);
			int tv = tileNumber / (_tileset.getSize().x / tileSize.x);

			// on récupère un pointeur vers le quad à définir dans le tableau de vertex
			sf::Vertex* quad = &_vertices[(i + j * width) * 4];

			// on définit ses quatre coins
			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			// on définit ses quatre coordonnées de texture
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}
	}
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
	load("Ressources/tileset.png", sf::Vector2u(64, 64));
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

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// on applique la transformation
	states.transform *= getTransform();

	// on applique la texture du tileset
	states.texture = &_tileset;

	// et on dessine enfin le tableau de vertex
	target.draw(_vertices, states);
}