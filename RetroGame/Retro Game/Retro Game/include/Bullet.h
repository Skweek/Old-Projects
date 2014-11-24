////////////////////////////////////////////////////////////
// File: Bullet.h
// Author: Nick Smith
// Date Created: 6th May 2013
// Brief: Bullet class
////////////////////////////////////////////////////////////

#ifndef _BULLET_H_
#define _BULLET_H_

#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet( Vec2 a_pPosition, int a_iDamage, int a_iDir, unsigned int a_iSprite, Vec2 a_uiSize = Vec2( 8.f, 8.f ), int a_iSpeed = FASTEST_SPEED );
	~Bullet();

	void Update( float a_fDelta );
	void OnCollision( int a_iEffect, int a_iModifier );
	
	int GetDirection();
	int GetDamage();
private:
	int m_iDir;
	int m_iDamage;

};

#endif