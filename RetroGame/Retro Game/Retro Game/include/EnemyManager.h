////////////////////////////////////////////////////////////
// File: EnemyManager.h
// Author: Nick Smith
// Date Created: 1st May 2013
// Brief: Enemy Manger
////////////////////////////////////////////////////////////

#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

class Enemy;
class BomberJet;
class FighterJet;

class Level;

#include <vector>
#include "Vec2.h"

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void CreateEnemy( int a_iEnemyType, Vec2 a_pPosition, Vec2 a_uiSize, int a_iSpeed, unsigned int a_iSprite, float a_fHealth );
	void Update( float a_fDelta, Level* LevelHandle );

	bool CheckCollision( Vec2 a_pBulletPos, Vec2 a_iBulletSize, int a_iDamage );
	void OnCollision( Enemy* a_iEnemy, int a_iEffect, int a_iModifier );

	//+===================================+//
	//	Get/Set enemy positions and size
	//	for collision
	//+===================================+//
	Vec2 GetEnemyPosition( Enemy* a_iEnemy );
	Vec2 GetEnemySize( Enemy* a_iEnemy );
	void SetEnemyPosition( Enemy* a_iEnemy, Vec2 a_pPos );
	void SetEnemySize( Enemy* a_iEnemy, Vec2 a_pSize );

	void DeleteEnemy( Enemy* a_pEnemy );

	std::vector<Enemy*> EnemyList;	

};

#endif