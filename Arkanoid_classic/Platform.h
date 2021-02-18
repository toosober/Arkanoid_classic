#pragma once

#include <random> // Для определения случайного направления полета шарика
#include "GameObject.h"
#include "Ball.h"
#include "Bonus.h"


class Platform : public GameObject
{

protected:

	Vector2f BallCollisionLeftEdge(Vector2f angleFlyBall, Ball& ball);			// Попали в верхнюю часть платформы в левый край (0-8 пиксель)
	Vector2f BallCollisionRightEdge(Vector2f angleFlyBall, Ball& ball);			// Попали в верхнюю часть платформы в правый край (0-8 пиксель с правого края)
	Vector2f BallCollisionStandart(Vector2f angleFlyBall, Ball& ball);			// Попали в верхнюю часть платформы
	Vector2f BallCollisionLeftWall(Vector2f angleFlyBall, Ball& ball);
	Vector2f BallCollisionRightWall(Vector2f angleFlyBall, Ball& ball);
	
	float CollisionLocation(Ball& ball);

public:
	Platform() {}
	virtual ~Platform() {};

	
	// Методы для всех наследников
	void Move(const float speed, const float time);
	void CollisionWithBonus(Bonus& bonus);



	// Виртуальные методы
	virtual Vector2f CollisionWithBall(Vector2f angleFlyBall, Ball& ball); // Cтолкновение с шариком
};

//---------------------------------------Большая платформа

class LargePlatform : public Platform
{
private:

	Vector2f BallCollisionLeftEdgePlus(Vector2f angleFlyBall, Ball& ball);
	Vector2f BallCollisionRightEdgePlus(Vector2f angleFlyBall, Ball& ball);
	Vector2f BallCollisionCenter(Vector2f angleFlyBall, Ball& ball);



public:
	LargePlatform();
	~LargePlatform() {}


	virtual Vector2f CollisionWithBall(Vector2f angleFlyBall, Ball& ball) override; // Переопределяет столкновение с шариком

};


//----------------------------------------Средняя платформа
class MediumPlatform : public Platform
{
private:
	

public:
	MediumPlatform();
	~MediumPlatform() {}
};


//-----------------------------------------Маленькая платформа

class SmallPlatform : public Platform
{
public:
	SmallPlatform();
	~SmallPlatform(){}

};


//---------------------------------------------Классы Фабричныого метода
class CreatorPlatform
{
public:
	virtual ~CreatorPlatform() {};
	virtual Platform* FactoryMethod() const = 0;

	Vector2f SomeCollisionWithBall(Vector2f angleFlyBall, Ball& ball);

	FloatRect SomeGetRect();
	void SomeSetPosition(Vector2f position);
	Vector2f SomeGetPosition();
	void SomeMove(const float speed, const float time);
};

class CreatorSmallPlatform : public CreatorPlatform
{
public:
	Platform* FactoryMethod() const override
	{
		return new SmallPlatform();
	}
};

class CreatorMediumPlatform : public CreatorPlatform
{
public:
	Platform* FactoryMethod() const override
	{
		return new MediumPlatform();
	}
};

class CreatorLargePlatform : public CreatorPlatform
{
public:
	Platform* FactoryMethod() const override
	{
		return new LargePlatform();
	}
	
};