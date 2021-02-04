#include "Border.h"

Border::Border(GameObject* gmbj)
{
	_leftTopCorner.setTexture(gmbj->GetTexture());
	_leftTopCorner.setTextureRect(sf::IntRect(1, 2, 31, 31));

	_leftBottomCorner.setTexture(gmbj->GetTexture());
	_leftBottomCorner.setTextureRect(sf::IntRect(1, 33, 31, -31));

	_rightTopCorner.setTexture(gmbj->GetTexture());
	_rightTopCorner.setTextureRect(sf::IntRect(29, 2, -28, 31));

	_rightBottomCorner.setTexture(gmbj->GetTexture());
	_rightBottomCorner.setTextureRect(sf::IntRect(29, 33, -28, -31));

	_horizontalWall.setTexture(gmbj->GetTexture());
	_horizontalWall.setTextureRect(sf::IntRect(65, 32, 37, 26));

	_verticalWall.setTexture(gmbj->GetTexture());
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





