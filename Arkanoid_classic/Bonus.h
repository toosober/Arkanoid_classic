#pragma once

#include "Config.h"
#include "GameObject.h"


class Bonus : public GameObject
{
private:

	BlockType _bonusType;

public:
	Bonus(BlockType blockType, Vector2f floatPosition);
	~Bonus() {}

};

