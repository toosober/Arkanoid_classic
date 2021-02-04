#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using std::string;

class GameObject
{
private:
	sf::Image image;
	sf::Texture texture;
	string path;



public:
	//конструторы
	GameObject(const string& path);
	GameObject(const GameObject&) = delete;
	~GameObject() {}

	//переопределенные операторы
	GameObject operator=(const GameObject& gmbj) const = delete;
	GameObject operator+(const GameObject& gmbj) const = delete;

	//Методы
	sf::Texture& GetTexture() { return texture; }
	void SetImage(string path);
};

class Platform : public sf::Sprite
{
private:
	GameObject* gmbj;					//указатель на класс где хранится изображение и текстура
	int coordX, coordY, width, hight;  //координаты начала спрайта и размер
	

public:
	Platform(GameObject* gmbj, int cX, int cY, int w, int h);
	Platform(const Platform&) = delete;
	~Platform() { }


	
};

class Balls : public sf::Sprite
{
private:
	GameObject* gmbj;					//указатель на класс где хранится изображение и текстура
	int coordX, coordY, width, hight;  //координаты начала спрайта и размер
	sf::Sprite ball;				//сам спрайт, храним его здесь чтобы обработка не занимала много места в main


	double startX, startY;         //координаты начальной точки 
	double distance;

public:
	Balls(GameObject* gmbj, int cX, int cY, int w, int h);
	Balls(const Balls&) = delete;
	~Balls() { }

	//Методы
	void Move(double dx, double dy, float time);
	void SetStartPosition(double StartX, double StartY);

};

