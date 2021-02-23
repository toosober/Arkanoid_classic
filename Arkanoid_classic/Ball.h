
#ifndef _BALL_H
#define _BALL_H

#include "GameObject.h"

class Ball : public GameObject
{
private:

	Vector2f _angleUnitCircle;   // ������ ����������� ������ ������
	Vector2f _speed;			 // ������ ��������
	
	float _acceleration;		 // ����������� ���������

	bool _flagInit;				 // ������������� ����������� ��� ������� ������ � ��������� (������ ����)
	bool _flagMove;				 // ���� ������� ������

	
public:
	Ball(float acceleration = 0.5);
	~Ball() { }


	//������
	void Move(double angleUnitCircleX, double angleUnityCircleY, float time);

	void SetSpeedFast();  // �������� �������
	void SetSpeedSlow();  // �������� �������
	void SetSpeed(float acceleration); // ������� ���������, ����� ����� ����� ���� ������ ������


	//��������
	void SetFlagMove(bool flagMove) { _flagMove = flagMove; }	
	bool GetFlagMove() { return _flagMove; }

	void SetFlagInit(bool flagInit) { _flagInit = flagInit; }
	bool GetFlagInit() { return _flagInit; }

	void SetAngleUnitCircle(Vector2f angleUnitCircle) { _angleUnitCircle = angleUnitCircle; }
	Vector2f GetAngleUnitCircle() { return _angleUnitCircle; }

	

};

#endif // _BALL_H