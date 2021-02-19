#pragma once

#include "config.h"

using std::string;
using namespace sf;

//---------------------------------------------Game Object--------------------------------------------------
class GameObject : public Sprite
{
protected:
	Image image;
	Texture texture;
	

	


public:
	//конструторы
	GameObject();
	GameObject(const GameObject&) = delete;
	virtual ~GameObject() {}

	//переопределенные операторы
	GameObject operator=(const GameObject&) const = delete;
	GameObject operator+(const GameObject&) const = delete;

	//ћетоды
	FloatRect GetRect();
	
};
