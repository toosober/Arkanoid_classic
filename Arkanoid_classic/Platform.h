
#ifndef _PLATFORM_H
#define _PLATFORM_H

#include "GameObject.h"
#include "Ball.h"



class Platform : public GameObject
{

protected:

	unsigned _Bullets;

	Vector2f BallCollisionLeftEdge(Ball& ball);			// Попали в верхнюю часть платформы в левый край (0-8 пиксель)
	Vector2f BallCollisionRightEdge(Ball& ball);		// Попали в верхнюю часть платформы в правый край (0-8 пиксель с правого края)
	Vector2f BallCollisionStandart(Ball& ball);			// Попали в верхнюю часть платформы
	Vector2f BallCollisionLeftWall(Ball& ball);			// Попали в левую стену платформы
	Vector2f BallCollisionRightWall(Ball& ball);		// Попали в правую стену платформы
	
	float CollisionLocation(Ball& ball);				// Определяем позицию столкновения на платформе
	

public:
	Platform(Image& img) : GameObject(img) { _Bullets = 0; }
	virtual ~Platform() {};

	
	// Методы для всех наследников
	void Move(const float speed, const float time);	
	void SetBullets() { _Bullets += 10; }
	void ReSetBulltes() { _Bullets = 0; }
	void Fire() { _Bullets -= 2; }
	bool GetBullets() { return _Bullets; }



	// Виртуальные методы
	virtual Vector2f CollisionWithBall(Ball& ball); // Функция обрабатывает столкновение
};

//---------------------------------------Большая платформа

class LargePlatform : public Platform
{
private:
	
	Vector2f BallCollisionLeftEdgePlus(Ball& ball);
	Vector2f BallCollisionRightEdgePlus(Ball& ball);
	Vector2f BallCollisionCenter(Ball& ball);



public:
	LargePlatform(Image& img);
	~LargePlatform() {}


	virtual Vector2f CollisionWithBall(Ball& ball) override; // Переопределяет обработку столкновения с шариком
	
};


//----------------------------------------Средняя платформа
class MediumPlatform : public Platform
{
private:
	
public:
	MediumPlatform(Image& img);
	~MediumPlatform() {}
};

//-----------------------------------------Маленькая платформа

class SmallPlatform : public Platform
{
public:
	SmallPlatform(Image& img);
	~SmallPlatform(){}

};

//-------------------------------------------Класс композиции платформ
class ConcretePlatform
{
private:
	Image& _image;

	Platform* _concretePlatform = NULL;
	MediumPlatform* _mediumPlatform = NULL;
	LargePlatform* _largePlatform = NULL;
	SmallPlatform* _smallPlatform = NULL;

	sizePlatform _sizePlatform;

public:
	ConcretePlatform(Image& img);
	~ConcretePlatform();

	Platform* GetInstance() { return _concretePlatform; }

	void ChangePlatform(int sizePlatform);
	sizePlatform GetSizePlatform() { return _sizePlatform; }

};

#endif