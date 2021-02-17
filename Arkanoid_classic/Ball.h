#pragma once

#include "GameObject.h"

class Balls : public GameObject
{
private:

	double angle_unit_circle_x = 0.0;  //направление полета шарика по x
	double angle_unit_circle_y = 0.0;  //направление полета шарика по y
	bool initialization = true;  //инициализаци€ направлени€ при запуске шарика с платформы (начало игры)
	bool change_angle = true;    //используетс€ дл€ изменени€ угла в методе Move
	unsigned score_ratio = 1;

	float speed_vector_x = 0; //вектор движени€ по x
	float speed_vector_y = 0; //вектор движени€ по y



	float ball_center_x = 0;    // центр шарика по х
	float ball_center_y = 0;    // центр шарика по y
	float ball_right_x = 0;     // правый край по х
	float ball_left_x = 0;      // левый край по х

	float platform_left_x = 0;  // левый край платформы по х это здесь хранить неправильно! исправить
	float platform_right_x = 0;	// правый край платформы по х это здесь хранить неправильно! исправить
	float platform_top_y = 0;   // верх платформы

	bool greenBonus = false; //поймали ли пурпурный бонус, надобно убрать это в бонус

	int ballPositionOnPlatform = 37; //позици€ шарика относительно платформы по х



	void CollisionLargePlatform(Platform* platform);
	void CollisionSmallAndMediumPlatform(Platform* platform);




public:
	Balls(Image& image, float coordX = 0, float coordY = 0, float width = 0, float height = 0, int speedX = 0, int speedY = 0);

	Balls(const Balls&) = delete;
	~Balls() { }

	//ћетоды
	void Move(double unit_circle_x, double unit_circle_y, float time, Platform* platform);
	void ChangeVector(int x);

	void SetSpeedFast(int x);  //тестовые функции
	void SetSpeedSlow(int x);  //тестовые функции


	void IncreaseValue_ScoreRatio() { this->score_ratio += 1; }
	unsigned GetScoreRatio() { return score_ratio; }

	void SetIsMove(bool isMove) { this->isMove = isMove; }
	bool GetIsMove() { return this->isMove; }

	void SetGreenBonus() { greenBonus = true; }
	void ResetGreenBonus() { greenBonus = false; }
	void SetBallPositionOnPlatform(int x) { ballPositionOnPlatform = x; }
	void ResetBallPositionOnPlatform() { ballPositionOnPlatform = 37; }
	int GetBallPositionOnPlatform() { return ballPositionOnPlatform; }






};