////////////////////////////////////////////////////////////
// File: FighterJet.h
// Author: Nick Smith
// Date Created: 17th May 2013
// Brief: Fighter Jet Enemy
////////////////////////////////////////////////////////////

#ifndef _FIGHTER_JET_H_
#define _FIGHTER_JET_H_

#include "Enemy.h"

class Level;
struct Timer;

class FighterJet : public Enemy
{
public:
	FighterJet( Vec2 a_pPosition, Vec2 a_uiSize, int a_iSpeed, unsigned int a_iSprite, float a_fHealth );

	void Update( float a_fDelta, Level* LevelHandle );	
	float GetHealth();

private:
	//+===================================+//
	//	Fire rate
	//+===================================+//
	Timer* m_pBulletTimer;
	float m_fBulletInterval;

	//+===================================+//
	//	AI movement
	//+===================================+//
	int m_iSideToFlyTo;
};

#endif // _FIGHTER_JET_H_