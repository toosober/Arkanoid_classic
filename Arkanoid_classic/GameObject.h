#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>
#include <list>
#include <random> //Для задания случайного направления полета шарика при первом его запуске с платформы
#include "Config.h" //Хранит константные значения конфигурации

using std::string;
using namespace sf;

//---------------------------------------------Game Object--------------------------------------------------
class GameObject : public Sprite
{
protected:
	static Image image;
	Texture texture;
	bool isMove;

	float coordX, coordY, width, height;	//координаты верхней левой точки, ширина и высота объекта
	float speedX;								//скорость движения по координате х
	float speedY;								//скорость движения по координате y



public:
	//конструторы
	GameObject(float coordX = 0, float coordY = 0, float width = 0, float height = 0, int speedX = 0, int speedY = 0);
	GameObject(const GameObject&) = delete;
	virtual ~GameObject() {}

	//переопределенные операторы
	GameObject operator=(const GameObject&) const = delete;
	GameObject operator+(const GameObject&) const = delete;

	//Методы
	FloatRect GetRect();
	Vector2f GetSpeed();
	void SetSpeed(Vector2f speed);
};

//----------------------------------------------Platform--------------------------------------------------


//------------------------------------------------Balls--------------------------------------------------


//------------------------------------------------Bonus--------------------------------------------------


//------------------------------------------------Block--------------------------------------------------



