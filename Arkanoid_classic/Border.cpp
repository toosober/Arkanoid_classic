#include "Border.h"

Border::Border(Image& image, float coordX, float coordY, float width, float height, int speedX, int speedY)
	: GameObject(image, coordX, coordY, width, height, speedX, speedY)
{
	_leftTopCorner.setTexture(texture);
	_leftTopCorner.setTextureRect(sf::IntRect(1, 2, 31, 31));

	_leftBottomCorner.setTexture(texture);
	_leftBottomCorner.setTextureRect(sf::IntRect(1, 33, 31, -31));

	_rightTopCorner.setTexture(texture);
	_rightTopCorner.setTextureRect(sf::IntRect(29, 2, -28, 31));

	_rightBottomCorner.setTexture(texture);
	_rightBottomCorner.setTextureRect(sf::IntRect(29, 33, -28, -31));

	_horizontalWall.setTexture(texture);
	_horizontalWall.setTextureRect(sf::IntRect(65, 32, 37, 26));

	_verticalWall.setTexture(texture);
	_verticalWall.setTextureRect(sf::IntRect(65, 1, 25, 29));
}


sf::Sprite Border::GetLeftTopCorner(int posX, int posY)
{
	_leftTopCorner.setPosition(posX, posY);
	return _leftTopCorner;
}

sf::Sprite Border::GetLeftBottomCorner(int posX, int posY)
{
	_leftBottomCorner.setPosition(posX, posY);
	return _leftBottomCorner;
}

sf::Sprite Border::GetRightTopCorner(int posX, int posY)
{
	_rightTopCorner.setPosition(posX, posY);
	return _rightTopCorner;
}

sf::Sprite Border::GetRightBottomCorner(int posX, int posY)
{
	_rightBottomCorner.setPosition(posX, posY);
	return _rightBottomCorner;
}

sf::Sprite Border::GetVerticalWall(int posX, int posY)
{
	_verticalWall.setPosition(posX, posY);
	return _verticalWall;
}

sf::Sprite Border::GetHorizontalWall(int posX, int posY)
{
	_horizontalWall.setPosition(posX, posY);
	return _horizontalWall;
}

void Border::CreateMap(RenderWindow& window)
{
	//Отрисовываем игровое поле из тайликов
	   //В тайлах не выдержан размер, поэтому коэффициенты в некоторых местах
	   //подогнанны вручную...
	for (int i = 0; i < horizontalSize; i++)
	{
		for (int j = 0; j < verticalSize; j++)
		{
			if (i == 0 && j == 0)
				window.draw(this->GetLeftTopCorner(0, 0));
			else if (i < horizontalSize - 1 && j == 0)
				window.draw(this->GetHorizontalWall(31 * i, 0));
			else if (i == horizontalSize - 1 && j == 0)
				window.draw(this->GetRightTopCorner((31 * i) - 4, 0));
			else if (j > 0 && i == 0)
				window.draw(this->GetVerticalWall(0, 29 * j));
			else if (j > 0 && i == horizontalSize - 1)
				window.draw(this->GetVerticalWall(31 * i, 29 * j));
		}
	}
}

void Border::CreateMenu(RenderWindow& window)
{
	//Отрисовываем меню из тайликов
	   //В тайлах не выдержан размер, поэтому коэффициенты в некоторых местах
	   //подогнанны вручную...
	for (int i = (horizontalSize); i < (horizontalSizeMenu); i++)
	{
		for (int j = 0; j < verticalSizeMenu; j++)
		{
			if (i == horizontalSize && j == 0)
				window.draw(this->GetLeftTopCorner((i * 31), 0));
			else if (i < horizontalSizeMenu - 1 && j == 0)
				window.draw(this->GetHorizontalWall(31 * i, 0));
			else if (i == horizontalSizeMenu - 1 && j == 0)
				window.draw(this->GetRightTopCorner((31 * i) - 4, 0));
			else if (j > 0 && i == horizontalSize && j < verticalSizeMenu - 1)
				window.draw(this->GetVerticalWall(i * 31, 29 * j));
			else if (j > 0 && i == horizontalSizeMenu - 1 && j < verticalSizeMenu - 1)
				window.draw(this->GetVerticalWall(i * 31, 29 * j));
			else if (j == verticalSizeMenu - 1 && i == horizontalSize)
				window.draw(this->GetLeftBottomCorner((i * 31), (j * 29)));
			else if (j == verticalSizeMenu - 1 && i == horizontalSizeMenu - 1)
				window.draw(this->GetRightBottomCorner((i * 31) - 4, (j * 29)));
			else if (j == verticalSizeMenu - 1 && i > horizontalSize && i < horizontalSizeMenu - 1)
				window.draw(this->GetHorizontalWall(31 * i, (j * 29 + 7)));
		}
	}
}





