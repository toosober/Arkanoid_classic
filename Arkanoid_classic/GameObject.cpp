
#include "GameObject.h"

//------------------------------------// GameObject //------------------------------------//

GameObject::GameObject()
{   
    this->image.loadFromFile(IMGPATH);
    this->texture.loadFromImage(image);    
}

FloatRect GameObject::GetRect()
{
    return FloatRect(this->getGlobalBounds().left, this->getGlobalBounds().top, this->getGlobalBounds().width, this->getGlobalBounds().height);
}








