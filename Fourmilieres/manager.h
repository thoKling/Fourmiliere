#pragma once

#include <vector>

///
/// Classe abstraite de manager pour g�rer les cas redondants
///
template <typename T>
class Manager
{
public:
	~Manager();

	void update();
	void draw(sf::RenderWindow& window);

private:
	// Ici comme on a pas de m�thode virtuelle pure on met le constructeur en priv�
	// https://www.developpez.net/forums/d296758/c-cpp/cpp/classes-abstraites-methode-virtuelle-pure/
	Manager();

	std::vector<T> _entityList;
};