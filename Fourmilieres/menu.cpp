#include "menu.h"
#include "application.h"
#include "config.h"
#include "game.h"

#include <string>

Menu::Menu() :
	_textboxMapSizeX("64"),
	_textboxMapSizeY("64"),
	_textboxObstaclesNbr("1000"),
	_textboxFoodNbr("500"),
	_textboxEvaporationRate("10")
{
	sf::RenderWindow& window = Application::getWindow();
	// création du menu
	if (!_font.loadFromFile("Ressources/comicz.ttf"))
		throw std::string("Impossible de charger la police d'écriture");

	// Titre
	_title.setFont(_font);
	_title.setString("Menu principal");
	_title.setCharacterSize(48);
	_title.setStyle(sf::Text::Bold | sf::Text::Underlined);
	_title.setOrigin(_title.getLocalBounds().left + _title.getLocalBounds().width / 2, 0);
	_title.setPosition(window.getSize().x / 2, 0);

	// Bouton Jouer
	_btnPlay.setFont(_font);
	_btnPlay.setString("Jouer");
	_btnPlay.setCharacterSize(24);
	_btnPlay.setOrigin(_btnPlay.getLocalBounds().left + _btnPlay.getLocalBounds().width / 2, 0);
	_btnPlay.setPosition(window.getSize().x / 2, 450);

	// Labels
	_labelMapSize.setFont(_font);
	_labelMapSize.setString("Taille de la carte :");
	_labelMapSize.setCharacterSize(18);
	_labelMapSize.setOrigin(_labelMapSize.getLocalBounds().left + _labelMapSize.getLocalBounds().width / 2, 0);
	_labelMapSize.setPosition(window.getSize().x / 2, 75);

	_labelObstaclesNbr.setFont(_font);
	_labelObstaclesNbr.setString("Nombre d'obstacles :");
	_labelObstaclesNbr.setCharacterSize(18);
	_labelObstaclesNbr.setOrigin(_labelObstaclesNbr.getLocalBounds().left + _labelObstaclesNbr.getLocalBounds().width / 2, 0);
	_labelObstaclesNbr.setPosition(window.getSize().x / 2, 175);

	_labelFoodNbr.setFont(_font);
	_labelFoodNbr.setString("Nombre de sources de nourritures :");
	_labelFoodNbr.setCharacterSize(18);
	_labelFoodNbr.setOrigin(_labelFoodNbr.getLocalBounds().left + _labelFoodNbr.getLocalBounds().width / 2, 0);
	_labelFoodNbr.setPosition(window.getSize().x / 2, 275);

	_labelEvaporationRate.setFont(_font);
	_labelEvaporationRate.setString("Evaporation de pheromones par tour :");
	_labelEvaporationRate.setCharacterSize(18);
	_labelEvaporationRate.setOrigin(_labelEvaporationRate.getLocalBounds().left + _labelEvaporationRate.getLocalBounds().width / 2, 0);
	_labelEvaporationRate.setPosition(window.getSize().x / 2, 375);

	// Textboxs
	//_textboxMapSizeX = TextBox("64");
	_textboxMapSizeX.setSize(90, 30);
	_textboxMapSizeX.setPosition(window.getSize().x / 2 - 100, 100);

	//_textboxMapSizeY = TextBox("64");
	_textboxMapSizeY.setSize(90, 30);
	_textboxMapSizeY.setPosition(window.getSize().x / 2, 100);

	//_textboxObstaclesNbr = TextBox("1000");
	_textboxObstaclesNbr.setSize(200, 30);
	_textboxObstaclesNbr.setPosition(window.getSize().x / 2 - (_textboxObstaclesNbr.getHitBox().width / 2), 200);

	//_textboxFoodNbr = TextBox("500");
	_textboxFoodNbr.setSize(200, 30);
	_textboxFoodNbr.setPosition(window.getSize().x / 2 - (_textboxFoodNbr.getHitBox().width / 2), 300);

	//_textboxEvaporationRate = TextBox("10");
	_textboxEvaporationRate.setSize(200, 30);
	_textboxEvaporationRate.setPosition(window.getSize().x / 2 - (_textboxEvaporationRate.getHitBox().width / 2), 400);

	// initialisation du focus
	_focusedTextbox = &_textboxMapSizeX;
	_focusedTextbox->focus();
}

Menu::~Menu()
{
}

void Menu::handleInputs(const sf::Vector2i& mousePixelPos, const sf::Vector2f& mousePos, const sf::Event& event)
{
	// Si le bouton gauche est pressé
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		// Si la souris est sur le bouton jouer
		if (_btnPlay.getGlobalBounds().contains(mousePos))
		{
			play();
		}
		// Meme chose avec les textboxs
		if (_textboxMapSizeX.getHitBox().contains(mousePos))
		{
			selectTextbox(_textboxMapSizeX);
		}
		if (_textboxMapSizeY.getHitBox().contains(mousePos))
		{
			selectTextbox(_textboxMapSizeY);
		}
		if (_textboxObstaclesNbr.getHitBox().contains(mousePos))
		{
			selectTextbox(_textboxObstaclesNbr);
		}
		if (_textboxFoodNbr.getHitBox().contains(mousePos))
		{
			selectTextbox(_textboxFoodNbr);
		}
		if (_textboxEvaporationRate.getHitBox().contains(mousePos))
		{
			selectTextbox(_textboxEvaporationRate);
		}
	}

	_focusedTextbox->handleInputs(event, mousePos);
}


void Menu::manageDraw(sf::RenderWindow& window)
{
	window.draw(_title);

	window.draw(_labelMapSize);
	window.draw(_labelObstaclesNbr);
	window.draw(_labelFoodNbr);
	window.draw(_labelEvaporationRate);

	window.draw(_textboxMapSizeX);
	window.draw(_textboxMapSizeY);
	window.draw(_textboxObstaclesNbr);
	window.draw(_textboxFoodNbr);
	window.draw(_textboxEvaporationRate);

	window.draw(_btnPlay);
}

void Menu::selectTextbox(TextBox& selectedTextbox)
{
	if (&selectedTextbox == _focusedTextbox)
		return;

	selectedTextbox.focus();
	_focusedTextbox->unfocus();
	_focusedTextbox = &selectedTextbox;
}
void Menu::play() {
	sf::Vector2u mapSize = sf::Vector2u(std::stoul(_textboxMapSizeX.getStr()), std::stoul(_textboxMapSizeY.getStr()));
	int obstaclesNbr = std::stoul(_textboxObstaclesNbr.getStr());
	int foodNbr = std::stoul(_textboxFoodNbr.getStr());
	int evaporationRate = std::stoul(_textboxEvaporationRate.getStr());
	Application::pushState(new game(mapSize, obstaclesNbr, foodNbr, evaporationRate));
}