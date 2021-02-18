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
	

	


public:
	//конструторы
	GameObject();
	GameObject(const GameObject&) = delete;
	virtual ~GameObject() {}

	//переопределенные операторы
	GameObject operator=(const GameObject&) const = delete;
	GameObject operator+(const GameObject&) const = delete;

	//Методы
	FloatRect GetRect();
	
};

