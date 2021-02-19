//#pragma once
//
//#include "GameObject.h"
//
//#include "Platform.h"
//
//class Ball : public GameObject
//{
//private:
//
//	Vector2f _angleUnitCircle;   // Вектор направления полета шарика
//	Vector2f _speed;			 // Вектор скорости
//	
//	int _acceleration;			  // Коээфициент ускорения
//
//	bool _flagInit;				 // Инициализация направления при запуске шарика с платформы (начало игры)
//	bool _flagMove;				 // Флаг запуска шарика
//
//	
//public:
//	Ball(float acceleration = 0.5);
//	~Ball() { }
//
//
//	//Методы
//	void Move(Vector2f angleUnitCircle, float time, CreatorPlatform* creatorPlatform);
//	
//
//	void SetSpeedFast();  //тестовые функции
//	void SetSpeedSlow();  //тестовые функции
//
//	//Свойства
//	void SetFlagMove(bool flagMove) { this->_flagMove = flagMove; }	
//	bool GetFlagMove() { return this->_flagMove; }
//
//	void SetFlagInit(bool flagInit) { this->_flagInit = flagInit; }
//	bool GetFlagInit() { return this->_flagInit; }
//
//	void SetSpeed(float acceleration);
//};
