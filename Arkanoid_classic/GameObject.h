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

//---------------------------------------------Game Object--------------------------------------------------
class GameObject : public Sprite
{
protected:
	Image& img;
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

//----------------------------------------------Platform--------------------------------------------------
class Platform : public GameObject
{
	enum Type { smallPlatform, mediumPlatform, largePlatform };
	unsigned typePlatform = mediumPlatform;
public:
	Platform(Image& image, float coordX = 0, float coordY = 0, float width = 0, float height = 0, int speedX = 0, int speedY = 0);
	~Platform() {}

	void ResetTypePlatform() { typePlatform = mediumPlatform; }
	void SetPlatform(bool choicePlatform);
	unsigned GetPlatformType() { return typePlatform; }
};

//------------------------------------------------Balls--------------------------------------------------
class Balls : public GameObject
{
private:

	double angle_unit_circle_x = 0.0;  //направление полета шарика по x
	double angle_unit_circle_y = 0.0;  //направление полета шарика по y
	bool initialization = true;  //инициализация направления при запуске шарика с платформы (начало игры)
	bool change_angle = true;    //используется для изменения угла в методе Move
	unsigned score_ratio = 1;

	float speed_vector_x = 0; //вектор движения по x
	float speed_vector_y = 0; //вектор движения по y



	float ball_center_x = 0;    // центр шарика по х
	float ball_center_y = 0;    // центр шарика по y
	float ball_right_x = 0;     // правый край по х
	float ball_left_x = 0;      // левый край по х

	float platform_left_x = 0;  // левый край платформы по х
	float platform_right_x = 0;	// правый край платформы по х
	float platform_top_y = 0;   // верх платформы


	
	void CollisionLargePlatform(Platform* platform);
	void CollisionSmallAndMediumPlatform(Platform* platform);
	
	


public:
	Balls(Image& image, float coordX = 0, float coordY = 0, float width = 0, float height = 0, int speedX = 0, int speedY = 0);

	Balls(const Balls&) = delete;
	~Balls() { }

	//Методы
	void Move(double unit_circle_x, double unit_circle_y, float time, Platform* platform);
	void ChangeVector(int x);

	void SetSpeedFast(int x);  //тестовые функции
	void SetSpeedSlow(int x);  //тестовые функции


	void IncreaseValue_ScoreRatio() { this->score_ratio += 1; }
	unsigned GetScoreRatio() { return score_ratio; }

	void SetIsMove(bool isMove) { this->isMove = isMove; }
	bool GetIsMove() { return this->isMove; }

	



};

//------------------------------------------------Bonus--------------------------------------------------
class Bonus : public GameObject
{
private:
	enum Type { blue, green, orange, pink, purple, red, yellow, no_color };

	unsigned bonusType;

public:
	Bonus(Image& image, float coordX = 0, float coordY = 0, float width = 0, float height = 0, unsigned bonusType = no_color, int speedX = 0, int speedY = 0);
	~Bonus() {}

	static void CollisionAndMove(std::list<Bonus*>& bonus, std::list<Bonus*>::iterator bns, Platform& platform, float time);
	
};

//------------------------------------------------Block--------------------------------------------------
class Block : public GameObject
{
private:
	enum type {blue, green, orange, pink, purple, red, yellow, no_color};

	int lives = 0;
	bool bonus = false;

	unsigned blockType;

public:
	Block(Image& image, float coordX = 0, float coordY = 0, float width = 0, float height = 0, unsigned blockType = no_color, bool bonus = false, int speedX = 0, int speedY = 0);
	Block(const Block&) = delete;
	~Block() { }


	static bool Collision(std::list<Block*>& blocks, std::list<Block*>::iterator blks, Balls& ball, std::list<Bonus*>& bonuses, std::list<Bonus*>::iterator bns);


};


