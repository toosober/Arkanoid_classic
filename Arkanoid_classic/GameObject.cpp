#include "GameObject.h"
#include <random>


GameObject::GameObject(const string& path)
{
    if (!image.loadFromFile(path))
    {
        std::cout << "Image not found" << std::endl;
        EXIT_FAILURE;
    }

    this->path = path;

    texture.loadFromImage(image);
    std::cout << path << std::endl;
}


void GameObject::SetImage(string path)
{
    if (!image.loadFromFile(path))
    {
        std::cout << "Image not found" << std::endl;
        EXIT_FAILURE;
    }

    this->path = path;
    texture.loadFromImage(image);
}


Platform::Platform(GameObject* gmbj, int cX, int cY, int w, int h)
{
    coordX = cX;
    coordY = cY;
    width = w;
    hight = h;

    this->setTexture(gmbj->GetTexture());
    this->setTextureRect(sf::IntRect(coordX, coordY, w, h));
}

Balls::Balls(GameObject* gmbj, int cX, int cY, int w, int h)
{
    coordX = cX;
    coordY = cY;
    width = w;
    hight = h;

    this->setTexture(gmbj->GetTexture());
    this->setTextureRect(sf::IntRect(coordX, coordY, w, h));

}

void Balls::Move(double distX, double distY, float time) //Координаты конечной точки
{
    distance = sqrt((distX - startX) * (distX - startX) + (distY - startY) * (distY - startY)); //теорема Пифагора
    if (distance > 2)
    {
        startX += 50 * time * (distX - startX) / distance;
        startY += 50 * time * (distY - startY) / distance;
    }
    this->setPosition(startX, startY);
}

void Balls::SetStartPosition(double StartX, double StartY)
{
    this->startX = StartX;
    this->startY = StartY;
}


