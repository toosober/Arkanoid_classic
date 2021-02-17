#pragma once

#include "GameObject.h"

class Platform : public GameObject
{
	enum Type { smallPlatform, mediumPlatform, largePlatform };
	unsigned typePlatform = mediumPlatform;

	unsigned rightBorder = 684; // Правая граница у средней платформы, 765 у большой и 715 у маленькой, это нужно для того, чтобы при столкновении правым бортом о границу
	//карты платформа не уезжала дальше. Костыль, временное решение.

public:
	Platform(Image& image, float coordX = 0, float coordY = 0, float width = 0, float height = 0, int speedX = 0, int speedY = 0);
	virtual ~Platform() {}

	void ResetTypePlatform();
	void SetPlatform(bool choicePlatform);
	unsigned GetPlatformType() { return typePlatform; }

	unsigned GetRightBorder() { return rightBorder; }

	//виртуальные методы
	virtual void Move();
	virtual void Collision();
};

//---------------------------------------Большая платформа

class LargePlatform : public Platform
{

};


//----------------------------------------Средняя платформа
class MediumPlatform : public Platform
{

};


//-----------------------------------------Маленькая платформа

class SmallPlatform : public Platform
{


};