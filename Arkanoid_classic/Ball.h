
#ifndef _BALL_H
#define _BALL_H

#include "GameObject.h"

class Ball : public GameObject
{
private:

	Vector2f _angleUnitCircle;   // Вектор направления полета шарика
	Vector2f _speed;			 // Вектор скорости
	
	float _acceleration;		 // Коээфициент ускорения

	bool _flagInit;				 // Инициализация направления при запуске шарика с платформы (начало игры)
	bool _flagMove;				 // Флаг запуска шарика

	
public:
	Ball(float acceleration = 0.5);
	~Ball() { }


	//Методы
	void Move(double angleUnitCircleX, double angleUnityCircleY, float time);

	void SetSpeedFast();  // Тестовые функции
	void SetSpeedSlow();  // Тестовые функции
	void SetSpeed(float acceleration); // Функция ускорения, нужна будет когда буду делать бонусы


	//Свойства
	void SetFlagMove(bool flagMove) { _flagMove = flagMove; }	
	bool GetFlagMove() { return _flagMove; }

	void SetFlagInit(bool flagInit) { _flagInit = flagInit; }
	bool GetFlagInit() { return _flagInit; }

	void SetAngleUnitCircle(Vector2f angleUnitCircle) { _angleUnitCircle = angleUnitCircle; }
	Vector2f GetAngleUnitCircle() { return _angleUnitCircle; }

	

};

#endif // _BALL_H