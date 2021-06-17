#pragma once

#include "drawableEntity.h"

class Food : public DrawableEntity
{
public:
	Food();
	~Food();

	void update();

	/// Renvoie le nombre de nourriture effectivement recolté
	int harvest();

	int getFoodLeft();

private:
	int _foodLeft;
};