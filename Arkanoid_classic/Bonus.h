#pragma once

#include "GameObject.h"

class Bonus : public GameObject
{
private:
	enum Type { blue, green, orange, pink, purple, red, yellow, no_color };

	unsigned bonusType;

public:
	Bonus(Image& image, unsigned bonusType = no_color, float coordX = 0, float coordY = 0, float width = 0, float height = 0, int speedX = 0, int speedY = 0);
	~Bonus() {}

	static void CollisionAndMove(std::list<Bonus*>& bonus, std::list<Bonus*>::iterator bns, Platform& platform, Balls& ball, float time);

	
};

