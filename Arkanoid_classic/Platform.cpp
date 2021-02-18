#include "Platform.h"


//-------------------------------------------------------------------------Platform

//движение платформы
void Platform::Move(const int& speed, const float& time)
{
    this->move(speed * time, 0);
}


// Пересечение платформы с шариком
// на вход принимаем шарик, который столкнулся с платформой и вектор его движения на единичной окружности
// возвращаем новый вектор движения шарика на единичной окружности
Vector2f Platform::CollisionWithBall(Vector2f angleFlyBall, Ball& ball) //Пересечение платформы с шариком
{
    float collisionLocation = this->CollisionLocation(ball);

    // Если центр шарика по координате х находится левее платформы
    if (collisionLocation < 0)
    {
        return this->BallCollisionLeftWall(angleFlyBall, ball);
    }
    // Если центр шарика по координате х находится на левом крае
    else if (collisionLocation < 8)
    {
        return this->BallCollisionLeftEdge(angleFlyBall, ball);
    }
    // Если центр шарика по координате х находится по середине между левым и правым краем
    else if (collisionLocation < this->GetRect().width - 8)
    {
        return this->BallCollisionStandart(angleFlyBall, ball);
    }
    // Если центр шарика по координате х находится на правом крае
    else if (collisionLocation < this->GetRect().width)
    {
        return this->BallCollisionRightEdge(angleFlyBall, ball);
    }
    // Если центр шарика по коориднае х находится правее платформы
    else
    {
        return this->BallCollisionRightWall(angleFlyBall, ball);
    }

}

Vector2f Platform::BallCollisionLeftEdge(Vector2f angleFlyBall, Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height);

    //Если приземлились на платформу практически прямо
    if (angleFlyBall.x > -0.001 && angleFlyBall.x < 0.001)
    {
        angleFlyBall.x = -0.9;
        angleFlyBall.y = sqrt(1 - pow(angleFlyBall.x, 2));        
    }
    else if (angleFlyBall.x > 0) //иначе если летим слева направо и ударяемся в левый угол, то должны отразиться обратно
    {
        angleFlyBall.x = -angleFlyBall.x;        //отражаемся по х
        angleFlyBall.y = -angleFlyBall.y;        //отражаемся по y                    
    }
    else if (angleFlyBall.x < 0) // Иначе если летим справа налево, то должны улететь под большим углом
    {
        angleFlyBall.x = -0.95;                                 //отражаемся по х
        angleFlyBall.y = sqrt(1 - pow(angleFlyBall.y, 2));        //отражаемся по y
    }

    return angleFlyBall;
    

}

Vector2f Platform::BallCollisionRightEdge(Vector2f angleFlyBall, Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height);

    //Если приземлились на платформу практически прямо
    if (angleFlyBall.x > -0.001 && angleFlyBall.x < 0.001)
    {
        angleFlyBall.x = -0.9;
        angleFlyBall.y = sqrt(1 - pow(angleFlyBall.x, 2));
    }
    else if (angleFlyBall.x < 0) //иначе если летим cправа налево и ударяемся в правый угол, то должны отразиться обратно
    {
        angleFlyBall.x = -angleFlyBall.x;        //отражаемся по х
        angleFlyBall.y = -angleFlyBall.y;        //отражаемся по y                    
    }
    else if (angleFlyBall.x > 0) // Иначе если летим слева направо, то должны улететь под большим углом
    {
        angleFlyBall.x = 0.95;                                 //отражаемся по х
        angleFlyBall.y = sqrt(1 - pow(angleFlyBall.y, 2));        //отражаемся по y
    }

    return angleFlyBall;


}

Vector2f Platform::BallCollisionStandart(Vector2f angleFlyBall, Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height);

    // Если по х практически не смещаемся и попадаем в центральную часть платформы, то должны улететь либо вправо, либо влево в зависимости от
    //состояния переменной change_angel
    if (angleFlyBall.x < 0.001 && angleFlyBall.y > -0.001)
    {
        std::random_device rd;
        std::mt19937 mersenne(rd());

        if (mersenne() % 2)
        {
            angleFlyBall.x = 0.5;
        }
        else
        {
            angleFlyBall.x = -0.5;
        }

        angleFlyBall.y = sqrt(1 - pow(angleFlyBall.x, 2));
    }
    // Иначе просто меняем направления полета по y
    else
    {
        angleFlyBall.y = -angleFlyBall.y;
    }

    return angleFlyBall;
}

Vector2f Platform::BallCollisionLeftWall(Vector2f angleFlyBall, Ball& ball)
{
    ball.setPosition(this->GetRect().left - ball.GetRect().width, ball.getPosition().y);
    angleFlyBall.x = -1 * abs(angleFlyBall.x);
}

Vector2f Platform::BallCollisionRightWall(Vector2f angleFlyBall, Ball& ball)
{
    ball.setPosition(this->GetRect().left + this->GetRect().width, ball.getPosition().y);
    angleFlyBall.x = abs(angleFlyBall.x);
}

float Platform::CollisionLocation(Ball& ball)
{
    return ball.GetRect().left + ( ball.GetRect().width / 2 ) - this->GetRect().left;
}





//-------------------------------------------------------------------------MediumPlatform

MediumPlatform::MediumPlatform()
{   
    this->setTextureRect(IntRect(MEDIUM_PLATFORM_LEFT, MEDIUM_PLATFORM_TOP, MEDIUM_PLATFORM_WIDTH, MEDIUM_PLATFORM_HEIGHT));
    
}



//--------------------------------------------------------------------------SmallPlatform
SmallPlatform::SmallPlatform()
{
    this->setTextureRect(IntRect(SMALL_PLATFORM_LEFT, SMALL_PLATFORM_TOP, SMALL_PLATFORM_WIDTH, SMALL_PLATFORM_HEIGHT));
}



//-------------------------------------------------------------------------------LargePlatform

LargePlatform::LargePlatform()
{
    this->setTextureRect(IntRect(LARGE_PLATFORM_LEFT, LARGE_PLATFORM_TOP, LARGE_PLATFORM_WIDTH, LARGE_PLATFORM_HEIGHT));
}

Vector2f LargePlatform::CollisionWithBall(Vector2f angleFlyBall, Ball& ball)
{
    float collisionLocation = this->CollisionLocation(ball);
    // Если центр шарика по координате х находится левее платформы
    if (collisionLocation < 0)
    {
        return this->BallCollisionLeftWall(angleFlyBall, ball);
    }
    // Если центр шарика по координате х находится на левом крае
    else if (collisionLocation < 8)
    {
        return this->BallCollisionLeftEdge(angleFlyBall, ball);
    }
    // Если попали в край платформы основной зоны, но не в сам угол
    else if (collisionLocation < 16)
    {
        return this->BallCollisionLeftEdgePlus(angleFlyBall, ball);
    }
    // Если попали в левую часть
    else if (collisionLocation < 58)
    {
        return this->BallCollisionStandart(angleFlyBall, ball);
    }
    // Если попали в самый центр
    else if (collisionLocation < 72)
    {
        return this->BallCollisionCenter(angleFlyBall, ball);
    }

    // Если попали в правую часть
    else if (collisionLocation < this->GetRect().width - 16)
    {
        return this->BallCollisionStandart(angleFlyBall, ball);
    }
    else if (collisionLocation < this->GetRect().width - 8)
    {
        return this->BallCollisionRightEdgePlus(angleFlyBall, ball);
    }
    // Если центр шарика по координате х находится на правом крае
    else if (collisionLocation < this->GetRect().width)
    {
        return this->BallCollisionRightEdge(angleFlyBall, ball);
    }
    // Если центр шарика по коориднае х находится правее платформы
    else
    {
        return this->BallCollisionRightWall(angleFlyBall, ball);
    }
}

Vector2f LargePlatform::BallCollisionLeftEdgePlus(Vector2f angleFlyBall, Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height); //если пересекли платформу, то выталкиваем шарик из платформы

    if (angleFlyBall.x < 0.001 && angleFlyBall.x > -0.001) //Если по х практически не смещаемся и попадаем в левый край, то должны слегка изменить свою траекторию
    {
        angleFlyBall.x += -0.35;
        angleFlyBall.y = sqrt(1 - pow(angleFlyBall.x, 2));
    }
    else if (angleFlyBall.x < 0) //иначе если летим справа налево и ударяемся в левый угол, то должны отразиться налево на чуть больший угол
    {
        if (angleFlyBall.x > -0.8)     //проверяем не слишком ли тупой угол, чтобы шарик не начал летать параллельно платформе
            angleFlyBall.x += -0.19;   //увеличиваем угол

        angleFlyBall.y = sqrt(1 - pow(angleFlyBall.x, 2)); //приводим угол по у в соовтетствии с х
    }
    // иначе, если летим слева направо то не меняем направление движения по х, а только по y
    else
    {
        angleFlyBall.y = -angleFlyBall.y;
    }

    return angleFlyBall;
        
}

Vector2f LargePlatform::BallCollisionRightEdgePlus(Vector2f angleFlyBall, Ball& ball)
{
    ball.setPosition(ball.getPosition().x, this->getPosition().y - ball.GetRect().height); //если пересекли платформу, то выталкиваем шарик из платформы

    if (angleFlyBall.x < 0.001 && angleFlyBall.x > -0.001) //Если по х практически не смещаемся и попадаем в правый край, то должны слегка изменить свою траекторию
    {
        angleFlyBall.x += +0.35;
        angleFlyBall.y = sqrt(1 - pow(angleFlyBall.x, 2));
    }
    else if (angleFlyBall.x > 0) //иначе если летим слева направо и ударяемся в правый угол, то должны отразиться вправо на чуть больший угол
    {
        if (angleFlyBall.x < 0.8)     //проверяем не слишком ли тупой угол, чтобы шарик не начал летать параллельно платформе
            angleFlyBall.x += 0.19;   //увеличиваем угол

        angleFlyBall.y = sqrt(1 - pow(angleFlyBall.x, 2)); //приводим угол по у в соовтетствии с х
    }
    // иначе, если летим справа налево то не меняем направление движения по х, а только по y
    else
    {
        angleFlyBall.y = -angleFlyBall.y;
    }

    return angleFlyBall;
}

Vector2f LargePlatform::BallCollisionCenter(Vector2f angleFlyBall, Ball& ball)
{
    ball.setPosition(this->getPosition().x, this->GetRect().top - ball.GetRect().height); //если пересекли платформу, то выталкиваем шарик из платформы

    std::random_device rd;
    std::mt19937 mersenne(rd());
    //Если по х практически не смещаемся и попадаем в центральную часть платформы, то должны улететь либо вправо, либо влево в зависимости от
    //состояния переменной change_angel
    if (angleFlyBall.x < 0.001 && angleFlyBall.x > -0.001)
    {
        if (mersenne()%2)
        {
            angleFlyBall.x = 0.5;                
        }
        else
        {
            angleFlyBall.x = -0.5;                
        }
        angleFlyBall.y = sqrt(1 - pow(angleFlyBall.x, 2));
    }
    else //Иначе если двигались слева направо или справа налево, то начинаем лететь вертикально вверх
    {
        angleFlyBall.x = 0;
        angleFlyBall.y = 1;        
    }

    return angleFlyBall;
}




//--------------------------------------------------------------------------------------Фабрика

Vector2f CreatorPlatform::SomeCollisionWithBall(Vector2f angleFlyBall, Ball& ball)
{
    Platform* platform = this->FactoryMethod();

    Vector2f result = platform->CollisionWithBall(angleFlyBall, ball);

    delete platform;
    return  result;
}

FloatRect CreatorPlatform::SomeGetRect()
{
    Platform* platform = this->FactoryMethod();

    FloatRect result = platform->GetRect();
    delete platform;
    return result;
}