
#ifndef _PLATFORM_H
#define _PLATFORM_H

#include "GameObject.h"
#include "Ball.h"


class Platform : public GameObject
{

protected:

	Vector2f BallCollisionLeftEdge(Vector2f angleUnitCircle, Ball& ball);			// Попали в верхнюю часть платформы в левый край (0-8 пиксель)
	Vector2f BallCollisionRightEdge(Vector2f angleUnitCircle, Ball& ball);			// Попали в верхнюю часть платформы в правый край (0-8 пиксель с правого края)
	Vector2f BallCollisionStandart(Vector2f angleUnitCircle, Ball& ball);			// Попали в верхнюю часть платформы
	Vector2f BallCollisionLeftWall(Vector2f angleUnitCircle, Ball& ball);			// Попали в левую стену платформы
	Vector2f BallCollisionRightWall(Vector2f angleUnitCircle, Ball& ball);			// Попали в правую стену платформы
	
	float CollisionLocation(Ball& ball);											// Определяем позицию столкновения на платформе
	

public:
	Platform() {}
	virtual ~Platform() {};

	
	// Методы для всех наследников
	void Move(const float speed, const float time);
	//void CollisionWithBonus(Bonus& bonus); столкновение платформы с бонусом


	// Виртуальные методы
	virtual Vector2f CollisionWithBall(Vector2f angleUnitCircle, Ball& ball); // Функция обрабатывает столкновение
};

//---------------------------------------Большая платформа

class LargePlatform : public Platform
{
private:
	
	Vector2f BallCollisionLeftEdgePlus(Vector2f angleUnitCircle, Ball& ball);
	Vector2f BallCollisionRightEdgePlus(Vector2f angleUnitCircle, Ball& ball);
	Vector2f BallCollisionCenter(Vector2f angleUnitCircle, Ball& ball);



public:
	LargePlatform();
	~LargePlatform() {}


	virtual Vector2f CollisionWithBall(Vector2f angleUnitCircle, Ball& ball) override; // Переопределяет обработку столкновения с шариком
	
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

//-------------------------------------------Класс композиции платформ
class ConcretePlatform
{
private:
	Platform* _concretePlatform = NULL;
	MediumPlatform* _mediumPlatform = NULL;
	LargePlatform* _largePlatform = NULL;
	SmallPlatform* _smallPlatform = NULL;

public:
	ConcretePlatform();
	~ConcretePlatform();

	Platform* GetInstance() { return _concretePlatform; }

	void ChangePlatform(int sizePlatform);

};

#endif