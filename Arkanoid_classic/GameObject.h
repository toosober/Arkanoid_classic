#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>
#include <list>
#include  <random> //Для задания случайного направления полета шарика при первом его запуске с платформы





using std::string;
using namespace sf;


class GameObject : public Sprite
{
protected:

	Texture texture;
	bool isMove;

	float coordX, coordY, width, height;	//координаты верхней левой точки, ширина и высота объекта
	float speedX;								//скорость движения по координате х
	float speedY;								//скорость движения по координате y



public:
	//конструторы
	GameObject(Image& image, float coordX = 0, float coordY = 0, float width = 0, float height = 0, int speedX = 0, int speedY = 0);
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

class Platform : public GameObject
{
private:


public:
	Platform(Image& image, float coordX = 0, float coordY = 0, float width = 0, float height = 0, int speedX = 0, int speedY = 0);
	~Platform() {}

};

class Balls : public GameObject
{
private:

	double angle_unit_circle_x = 0.0;  //направление полета шарика по x
	double angle_unit_circle_y = 0.0;  //направление полета шарика по y
	bool initialization = true;  //инициализация направления при запуске шарика с платформы (начало игры)
	bool change_angle = true;    //используется для изменения угла в методе Move
	int counter = 0;

public:
	Balls(Image& image, float coordX = 0, float coordY = 0, float width = 0, float height = 0, int speedX = 0, int speedY = 0);

	Balls(const Balls&) = delete;
	~Balls() { }

	//Методы
	void Move(double unit_circle_x, double unit_circle_y, float time, Platform* platform);
	void ChangeVector(int x);

	void SetSpeedFast(int x);  //тестовые функции
	void SetSpeedSlow(int x);  //тестовые функции

	void SetIsMove(bool isMove) { this->isMove = isMove; }
	bool GetIsMove() { return this->isMove; }



};

class Block : public GameObject
{
private:
	int lives = 0;

public:
	Block(Image& image, float coordX = 0, float coordY = 0, float width = 0, float height = 0, int speedX = 0, int speedY = 0);
	Block(const Block&) = delete;
	~Block() { }


	static bool Collision(std::list<Block*>& blocks, std::list<Block*>::iterator blks, Balls& ball);


};

