#include "TextBox.h"

#include "utils.h"
#include <iostream>
#include <string>

std::vector<sf::Uint32> digitsUnicode { 0x000030, 0x000031, 0x000032, 0x000033, 0x000034, 0x000035, 0x000036, 0x000037, 0x000038, 0x000039 };

TextBox::TextBox(std::string placeholder)
{
	_hasFocus = false;

	_rect.setFillColor(sf::Color::White);

	// Initialisation de la chaîne de charactères
	_str = placeholder;

	// Création du texte à afficher
	if (!_font.loadFromFile("Ressources/comicz.ttf"))
		throw std::string("Impossible de charger la police d'écriture");

	_text.setFont(_font);
	_text.setString(_str);
	_text.setCharacterSize(8);
	_text.setFillColor(sf::Color::Black);

	// Création du curseur
	_cursor.setFont(_font);
	_cursor.setString("");
	_cursor.setCharacterSize(10);
	_cursor.setFillColor(sf::Color::Black);
}

TextBox::~TextBox()
{
}



std::string TextBox::getStr()
{
	return _str;
}

void TextBox::setSize(int x, int y)
{
	// Changement de taille du rectangle
	sf::Vector2f size(x, y);
	_rect.setSize(size);

	// Changement de taille du texte
	_text.setCharacterSize(y - 10);

	// CHangement de taille du curseur
	_cursor.setCharacterSize(y - 10);
}



sf::FloatRect TextBox::getHitBox()
{
	sf::FloatRect res = _rect.getGlobalBounds();
	res.left = getPosition().x;
	res.top = getPosition().y;
	return res;
}

void TextBox::focus()
{
	updateCursorPosition();
	_hasFocus = true;
	_cursor.setString("|");
}

void TextBox::unfocus()
{
	_hasFocus = false;
	_cursor.setString("");
}

void TextBox::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// on applique la transformation de l'entité -- on la combine avec celle qui a été passée par l'appelant
	states.transform *= getTransform(); // getTransform() est définie par sf::Transformable

	// on dessine le rectangle
	target.draw(_rect, states);
	target.draw(_text, states);
	target.draw(_cursor, states);
}

void TextBox::handleInputs(const sf::Event& event, const sf::Vector2f& mousePos)
{
	if (_hasFocus && event.type == sf::Event::TextEntered)
	{
		// Si l'utilisateur tape sur BackSpace, retrait du dernier charactère
		if (event.text.unicode == 0x000008)
		{
			if (_str.size() > 0)
			{
				_str.pop_back();
				_text.setString(_str);

				updateCursorPosition();
			}
		}

		// Sinon, ajout du charactère tapé par l'utilisateur
		else if (Utils::contains(digitsUnicode, event.text.unicode))
		{
			if (_str.size() < 5)
			{
				_str.push_back(event.text.unicode);
				_text.setString(_str);

				updateCursorPosition();
			}
		}
	}
}

void TextBox::updateCursorPosition()
{
	_cursor.setPosition(_text.getGlobalBounds().left + _text.getLocalBounds().width, _text.getGlobalBounds().top);
}
