#pragma once

#include <SFML/Graphics.hpp>
#include "gamestate.h"
#include "textbox.h"

class Menu : public GameState
{
public:
	Menu();
	~Menu();

	void update() {  };
	void handleInputs(const sf::Vector2i& mousePixelPos, const sf::Vector2f& mousePos, const sf::Event& event);
	void manageDraw(sf::RenderWindow& window);

private:
	sf::Font _font;
	sf::Text _title;

	sf::Text _labelMapSize;
	sf::Text _labelObstaclesNbr;
	sf::Text _labelFoodNbr;
	sf::Text _labelEvaporationRate;

	TextBox _textboxMapSizeX;
	TextBox _textboxMapSizeY;
	TextBox _textboxObstaclesNbr;
	TextBox _textboxFoodNbr;
	TextBox _textboxEvaporationRate;

	TextBox* _focusedTextbox;

	sf::Text _btnPlay;

	void selectTextbox(TextBox& selectedTextbox);
};