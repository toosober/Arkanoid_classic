
#include "Bonus.h"


Bonus::Bonus(BlockType blockType, Vector2f startPosition) : _bonusType(blockType)
{
    this->setPosition(startPosition);
    this->setTexture(texture);
    switch (_bonusType)
    {
    case BLUE:
        this->setTextureRect(sf::IntRect(BLUE_BONUS_LEFT, BLUE_BONUS_TOP, BONUS_WIDTH, BONUS_HEIGHT));
        break;
    case GREEN:
        this->setTextureRect(sf::IntRect(GREEN_BONUS_LEFT, GREEN_BONUS_TOP, BONUS_WIDTH, BONUS_HEIGHT));
        break;    
    case PINK:
        this->setTextureRect(sf::IntRect(PINK_BONUS_LEFT, PINK_BONUS_TOP, BONUS_WIDTH, BONUS_HEIGHT));
        break;
    case PURPLE:
        this->setTextureRect(sf::IntRect(PURPLE_BONUS_LEFT, PURPLE_BONUS_TOP, BONUS_WIDTH, BONUS_HEIGHT));
        break;
    case RED:
        this->setTextureRect(sf::IntRect(RED_BONUS_LEFT, RED_BONUS_TOP, BONUS_WIDTH, BONUS_HEIGHT));
        break;
    case YELLOW:
        this->setTextureRect(sf::IntRect(YELLOW_BONUS_LEFT, YELLOW_BONUS_TOP, BONUS_WIDTH, BONUS_HEIGHT));
        break;
    default:
        throw ("invalid argument bonusType");
        break;
    }
}



//
//Bonus::Bonus(Image& image, unsigned bonusType, float coordX, float coordY, float width, float height, int speedX, int speedY)
//    : GameObject(image, coordX, coordY, width, height, speedX, speedY)
//{
//    this->bonusType = bonusType;
//    this->setTexture(texture);
//    this->width = 27;
//    this->height = 30;
//    switch (bonusType)
//    {
//    case blue:
//        this->coordX = 456;
//        this->coordY = 449;
//        break;
//    case green:
//        this->coordX = 488;
//        this->coordY = 449;
//        break;
//    case pink:
//        this->coordX = 520;
//        this->coordY = 449;
//        break;
//    case purple:
//        this->coordX = 553;
//        this->coordY = 449;
//        break;
//    case red:
//        this->coordX = 456;
//        this->coordY = 482;
//        break;
//    case yellow:
//        this->coordX = 488;
//        this->coordY = 481;
//        break;
//
//    }
//
//    this->setTextureRect(sf::IntRect(this->coordX, this->coordY, this->width, this->height));
//
//}
//
//void Bonus::CollisionAndMove(std::list<Bonus*>& bonuses, std::list<Bonus*>::iterator bns, Platform& platform, Balls& ball, float time)
//{
//    std::random_device rd;
//    std::mt19937 mersenne(rd());
//    for (bns = bonuses.begin(); bns != bonuses.end();)
//    {
//        (*bns)->move(0, (0.1 * time));
//
//        if ((*bns)->GetRect().intersects(platform.GetRect()))
//        {
//            switch ((*bns)->bonusType)
//            {
//            case blue:
//                platform.SetPlatform(mersenne() % 2);
//                break;
//            case green:
//                ball.SetGreenBonus();
//                break;
//            case pink:
//                break;
//            case purple:
//
//                break;
//            case red:
//                break;
//            case yellow:
//                Menu::GetInstance().SetCountlives(1);
//                break;
//            default:
//                break;
//            }
//
//            bns = bonuses.erase(bns);
//        }
//
//        else
//        {
//            bns++;
//        }
//
//
//    }
//}