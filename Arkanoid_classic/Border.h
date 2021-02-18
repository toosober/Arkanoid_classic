#pragma once

#include "GameObject.h"

class Border : public GameObject
{
private:
	//тайлы границ (углы и стены)
	Sprite _verticalWall;
	Sprite _horizontalWall;
	Sprite _leftTopCorner;
	Sprite _leftBottomCorner;
	Sprite _rightTopCorner;
	Sprite _rightBottomCorner;

	//Переменные отвечающие за количество тайликов
   //На данный момент тайлы вырезаны кустарным способом и поэтому отличаются по своему размеру
   //Поэтому карту нельзя создать автоматически приходится немного подгадывать с размером тайлов
	//Будет время это нужно исправть
	


public:
	//конструторы
	Border(Image& image, float coordX = 0, float coordY = 0, float width = 0, float height = 0, int speedX = 0, int speedY = 0);
	Border(const Border&) = delete;

	~Border() {}

	//переопределенные операторы
	Border operator=(const GameObject& gmbj) const = delete;
	Border operator+(const GameObject& gmbj) const = delete;

	//Методы получения картинок стенок карты
	Sprite GetLeftTopCorner(int posX, int posY);
	Sprite GetLeftBottomCorner(int posX, int posY);
	Sprite GetRightTopCorner(int posX, int posY);
	Sprite GetRightBottomCorner(int posX, int posY);
	Sprite GetVerticalWall(int posX, int posY);
	Sprite GetHorizontalWall(int posX, int posY);

	void CreateMap(RenderWindow& window);
	void CreateMenu(RenderWindow& window);


};

