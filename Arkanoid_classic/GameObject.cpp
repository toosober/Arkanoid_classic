
#include "GameObject.h"

//------------------------------------// GameObject //------------------------------------//

GameObject::GameObject(Image& img) : _image(img)
{   
    _texture.loadFromImage(_image);  
}

FloatRect GameObject::GetRect()
{
    return FloatRect(this->getGlobalBounds().left, this->getGlobalBounds().top, this->getGlobalBounds().width, this->getGlobalBounds().height);
}








