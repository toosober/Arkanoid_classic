
#include "GameObject.h"
#include "Menu.h"
#include <random>



//------------------------------------// GameObject //------------------------------------//

GameObject::GameObject(float coordX, float coordY, float width, float height, int speedX, int speedY)
{   
    this->image.loadFromFile(ImgPath);
    this->texture.loadFromImage(image);
    this->coordX = coordX;
    this->coordY = coordY;
    this->width = width;
    this->height = height;
    this->speedX = speedX;
    this->speedY = speedY;
    isMove = false;
}

FloatRect GameObject::GetRect()
{
    return FloatRect(this->getPosition().x, this->getPosition().y, width, height);
}

Vector2f GameObject::GetSpeed()
{
    return Vector2f(speedX, speedY);
}

void GameObject::SetSpeed(Vector2f speed)
{
    speedX = speed.x;
    speedY = speed.y;
}

//------------------------------------// Platform //------------------------------------//



//------------------------------------// Balls //------------------------------------//





//------------------------------------// Bonus //------------------------------------//



//------------------------------------// Block //------------------------------------//





