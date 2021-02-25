

#ifndef _BONUS_H
#define _BONUS_H

#include "Config.h"
#include "GameObject.h"
#include "Platform.h"
#include "Menu.h"




class Bonus : public GameObject
{
private:

	BlockType _bonusType;
	double _speedFall = 0.1;

public:
	Bonus(BlockType blockType, Vector2f startPosition);
	~Bonus() {}

	void Move(float time);

	//обработка столкновения с платформой
	void CollisionWithPlatform(ConcretePlatform* platform, std::list<Ball*>& ball);

	//функции бафов
	void MultipleBall(std::list<Ball*>& ball); // Из каждого шарика в игре вылетает еще два шарика
	void ChangePlatform(ConcretePlatform* platform);   // Увеличиваем или уменьшаем платформу
	void LaserOnBoard(ConcretePlatform* platform);	   // Устанавливаем лазер на платформу
	void ChangeSpeedBall(std::list<Ball*>& ball); // Ускоряем или замедляем шарик(и)
	void CatchBall(std::list<Ball*>& ball);    // Если шарик на экране остался один, он приклеивается к платформе
	void AddLive();							   // Этот бонус добавляет одну жизнь игроку

	

};

#endif // _BONUS_H