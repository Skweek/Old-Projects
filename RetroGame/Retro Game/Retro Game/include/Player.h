////////////////////////////////////////////////////////////
// File: Player.h
// Author: Nick Smith
// Date Created: 30th April 2013
// Brief: Player class
////////////////////////////////////////////////////////////

#ifndef _PLAYER_H_
#define _PLAYER_H_

class Level;
struct Timer;

#include "Entity.h"

class Player : public Entity
{
public:
	//+===================================+//
	//	Constructor
	//+===================================+//
	Player( Vec2 a_pPosition, Vec2 a_uiSize, int a_iSpeed, unsigned int a_iSprite, float a_fHealth );

	void Update( float a_fDelta, Level* LevelHandle, bool* a_iKeys );
	void OnCollision( int a_iEffect, int a_iModifier );

	//+===================================+//
	//	Used by Level to get information to 
	//	display
	//+===================================+//
	float GetHealth();
	float GetLives();
	
private:
	//+===================================+//
	//	Movement bools
	//+===================================+//
	bool m_bCanMoveLeft;
	bool m_bCanMoveRight;
	bool m_bCanMoveUp;
	bool m_bCanMoveDown;

	float m_fLives;

	//+===================================+//
	//	Fire rate
	//+===================================+//
	Timer* m_pBulletTimer;
	float m_fBulletInterval;

};

#endif