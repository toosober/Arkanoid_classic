//#pragma once
//
//
//
//#include "GameObject.h"
//#include "Ball.h"
//
//
//class Block : public GameObject
//{
//private:
//	
//	std::list<Bonus*> bonus;
//
//	int _strength = 0;    // Количество попаданий в блок до разрушения 
//	
//	bool _bonus = false;  // Если true то при попадании из блока выпадает бонус
//	BlockType _blockType; // Цвет блока отвечает за подгуженную текстуру
//
//
//	Vector2f BallCollisionLeftTopCorner(Vector2f angleUnitCircle, Ball& ball);		// Столкновение с левым верхним углом
//	Vector2f BallCollisionRightTopCorner(Vector2f angleUnitCircle, Ball& ball);		// Столкновение с правым верхним углом
//	Vector2f BallCollisionLeftBottomCorner(Vector2f angleUnitCircle, Ball& ball);	// Столкновение с левым нижним углом
//	Vector2f BallCollisionRightBottomCorner(Vector2f angleUnitCircle, Ball& ball);	// Столкновение с правым нижним углом
//	Vector2f BallCollisionLeftWall(Vector2f angleUnitCircle, Ball& ball);			// Столкновение с левой стенкой
//	Vector2f BallCollisionBottomWall(Vector2f angleUnitCircle, Ball& ball);			// Столкновение с низом
//	Vector2f BallCollisionTopWall(Vector2f angleUnitCircle, Ball& ball);			// Столкновение с верхом
//	Vector2f BallCollisionRightWall(Vector2f angleUnitCircle, Ball& ball);			// Столкновение с правой стенкой
//
//public:
//	Block(BlockType blockType = NO_BONUS, bool bonus = false );
//	~Block() { }
//
//
//	Vector2f BallCollision(Vector2f angleUnitCircle, Ball& ball);
//
//	void BonusCreate();
//	
//
//};
//
