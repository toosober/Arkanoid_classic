

#ifndef _BONUS_H
#define _BONUS_H

#include "Config.h"
#include "GameObject.h"
#include "Platform.h"
#include "Menu.h"


class Bonus : public GameObject
{
private:

	BlockType _bonusType;
	double _speedFall = 0.1;

public:
	Bonus(BlockType blockType, Vector2f startPosition);
	~Bonus() {}

	void Move(float time);
	void CollisionWithPlatform(Platform& platform);

};

#endif // _BONUS_H