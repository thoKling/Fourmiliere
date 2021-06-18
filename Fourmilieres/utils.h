#pragma once

#include <SFML/Graphics.hpp>

class Utils
{
public:
	// Récupération du numéro de quadrant dans lequel se situe la pos2 par rapport a la pos1
	static int getQuadrant(const sf::Vector2f& pos1, const sf::Vector2f& pos2);
	// Renvoit le vecteur unitaire de la startPos à la endPos
	static sf::Vector2f getVecUnit(const sf::Vector2f& startPos, const sf::Vector2f& endPos);
	// Renvoit la distance entre 2 coordonnées
	static double distance(const sf::Vector2f& pos1, const sf::Vector2f& pos2);
	// Fonction split pour les strings, renvoit les différents morceaux de la chaine entre les delimiter
	static std::vector<std::string> split(std::string stringToSplit, std::string delimiter);
	// Fonction pour voir si un vecteur contient une valeur donnée
	template <typename T>
	static bool contains(std::vector<T> array, T object);
};

template<typename T>
inline bool Utils::contains(std::vector<T> array, T object)
{
	for (auto val : array) {
		if (val == object) {
			return true;
		}
	}
	return false;
}
