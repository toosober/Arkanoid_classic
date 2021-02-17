#pragma once

#include "GameObject.h"

class Block : public GameObject
{
private:
	enum type { blue, green, orange, pink, purple, red, yellow, no_color };

	int lives = 0;
	bool bonus = false;

	unsigned blockType;

public:
	Block(Image& image, float coordX = 0, float coordY = 0, float width = 0, float height = 0, bool bonus = false, unsigned blockType = no_color, int speedX = 0, int speedY = 0);
	Block(const Block&) = delete;
	~Block() { }


	static bool Collision(std::list<Block*>& blocks, std::list<Block*>::iterator blks, Balls& ball, std::list<Bonus*>& bonuses, std::list<Bonus*>::iterator bns);


};