#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class TextBox : public sf::Drawable, public sf::Transformable
{
public:
	TextBox(std::string placeholder);
	~TextBox();

	std::string getStr();

	void setSize(int x, int y);


	sf::FloatRect getHitBox();
	void focus();
	void unfocus();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void handleInputs(const sf::Event& event, const sf::Vector2f& mousePos);

private:
	void updateCursorPosition();
	bool _hasFocus;

	sf::RectangleShape _rect;

	sf::Font _font;
	sf::Text _text;
	std::string _str;

	sf::Text _cursor;
};