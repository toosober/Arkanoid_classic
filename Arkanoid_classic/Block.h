#pragma once

#include "GameObject.h"
#include "Ball.h"

class Block : public GameObject
{
private:
	enum _type { blue, green, orange, pink, purple, red, yellow, no_color };

	int _strength = 0;
	
	bool _bonus = false;
	unsigned _blockType;

public:
	Block(bool bonus = false, unsigned blockType = no_color);
	~Block() { }


	bool Collision(Ball& ball);


};