////////////////////////////////////////////////////////////
// File: BomberJet.h
// Author: Nick Smith
// Date Created: 17th May 2013
// Brief: Bomber Jet Enemy
////////////////////////////////////////////////////////////

#ifndef _BOMBER_JET_H_
#define _BOMBER_JET_H_

#include "Enemy.h"

class Level;
struct Timer;

class BomberJet : public Enemy
{
public:
	BomberJet( Vec2 a_pPosition, Vec2 a_uiSize, int a_iSpeed, unsigned int a_iSprite, float a_fHealth );

	void Update( float a_fDelta, Level* LevelHandle );	
	float GetHealth();

private:
	//+===================================+//
	//	Fire rate
	//+===================================+//
	Timer* m_pBulletTimer;
	float m_fBulletInterval;
};

#endif // _BOMBER_JET_H_