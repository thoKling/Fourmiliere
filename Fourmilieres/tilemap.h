#pragma once
#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap();
	~TileMap();

	void generateMap(const sf::Vector2u size, const int obstaclesNbr, const int foodNbr);
	sf::Vector2u getMapSize();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void load(const std::string& tileset, sf::Vector2u tileSize);
	void randomizeTile(int nbr, int tileNbr);

	std::vector<std::vector<int>> _tiles;

	sf::VertexArray _vertices;
	sf::Texture _tileset;
};