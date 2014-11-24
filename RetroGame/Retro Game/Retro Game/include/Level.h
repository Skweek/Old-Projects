////////////////////////////////////////////////////////////
// File: Level.h
// Author: Nick Smith
// Date Created: 6th April 2013
// Brief: Level class
////////////////////////////////////////////////////////////

#ifndef _LEVEL_H_
#define _LEVEL_H_

class Collision;
class Player;
class EnemyManager;
class Bullet;

#include <vector>
#include "Vec2.h"

struct Tile;
struct Timer;

class Level
{
public:
	//+===================================+//
	//	Constructor
	//+===================================+//
	Level();
	~Level();

	//+===================================+//
	//	Level creation/deletion functions
	//+===================================+//
	void CreateLevel();
	void DeleteLevel();

	//+===================================+//
	//	Update level and display
	//+===================================+//
	void Update( float a_fDelta );
	void DrawLevel();

	//+===================================+//
	//	Player and enemy functions
	//+===================================+//
	void ShootBullet( Vec2 a_pPosition, int a_iDamage, int a_iDir );
	void NewEnemyWave();
	Vec2 GetPlayerInfo();
	int GetScore();

private:
	void MoveLevel();

	// Variables for determining which rows are currently being drawn
	int m_iCurTopRow;
	int m_iCurBotRow;

	int m_iScore;

	//+===================================+//
	//	Tiles
	//+===================================+//
	Tile** MapGrid;

	//+===================================+//
	//	Object handles
	//+===================================+//
	Collision* Collisions;
	EnemyManager* EnemiesManager;
	std::vector<Bullet*> Bullets;
	Player* Player1;

	//+===================================+//
	//	Timed events (enemy spawning)
	//+===================================+//
	int m_iWaveInterval;
	int m_iNumberOfEnemiesToSpawn;
	int m_iRatioOfEnemyTypes;
	Timer* EnemyWaves;
	
	//+===================================+//
	//	Collision detection functions
	//+===================================+//
	void PlayerOutOfBounds();
	void EnemyOutOfBounds();
	void BulletOutOfBounds();
	void EnemyToPlayerCollision();
	void BulletCollisions();

	void DeleteBullet( Bullet* a_pBullet );
};



#endif