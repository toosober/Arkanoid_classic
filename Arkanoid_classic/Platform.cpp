#include "Platform.h"


Platform::Platform(Image& image, float coordX, float coordY, float width, float height, int speedX, int speedY)
    : GameObject(image, coordX, coordY, width, height, speedX, speedY)
{
    this->setTexture(texture);
    this->setTextureRect(sf::IntRect(coordX, coordY, width, height));
}

void Platform::SetPlatform(bool choicePlatformType)
{
    if (this->typePlatform == largePlatform || this->typePlatform == smallPlatform)
    {
        this->typePlatform = mediumPlatform;
        this->coordX = 58;
        this->coordY = 302;
        this->width = 90;
        this->height = 31;
        this->setTextureRect(sf::IntRect(coordX, coordY, width, height));
        this->rightBorder = 684;
    }
    else if (this->typePlatform == mediumPlatform)
    {
        if (choicePlatformType == true)
        {
            this->coordX = 148;
            this->coordY = 302;
            this->width = 128;
            this->height = 31;
            this->typePlatform = largePlatform;
            this->setTextureRect(sf::IntRect(coordX, coordY, width, height));
            this->rightBorder = 645;
        }
        else
        {
            this->coordX = 0;
            this->coordY = 302;
            this->width = 58;
            this->height = 31;
            this->typePlatform = smallPlatform;
            this->setTextureRect(sf::IntRect(coordX, coordY, width, height));
            this->rightBorder = 715;
        }

    }
}

void Platform::ResetTypePlatform()
{
    this->typePlatform = mediumPlatform;
    this->coordX = 58;
    this->coordY = 302;
    this->width = 90;
    this->height = 31;
    this->setTextureRect(sf::IntRect(coordX, coordY, width, height));
    this->rightBorder = 684;
}