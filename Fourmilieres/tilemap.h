#pragma once
#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap();
	~TileMap();

	void generateMap(sf::Vector2u size, int obstaclesNbr);
	sf::Vector2u getMapSize();
	bool isObstacle(sf::Vector2u position);
	bool isAnthill(sf::Vector2u position);

	void changeTile(sf::Vector2u position, int tileNumber);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void loadAllTiles();
	void loadTile(sf::Vector2u position);

	void randomizeTile(int nbr, int tileNbr);

	std::vector<std::vector<int>> _tiles;

	sf::Vector2u _tileSize;

	sf::VertexArray _vertices;
	sf::Texture _tileset;
};