////////////////////////////////////////////////////////////
// File: Enemy.h
// Author: Nick Smith
// Date Created: 1st May 2013
// Brief: Enemy class
////////////////////////////////////////////////////////////

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Entity.h"
class Level;

class Enemy : public Entity
{
public:
	Enemy( Vec2 a_pPosition, Vec2 a_uiSize, int a_iSpeed, unsigned int a_iSprite, float a_fHealth );

	void OnCollision( int a_iEffect, int a_iModifier );

	virtual void Update( float a_fDelta, Level* LevelHandle ) = 0;

	virtual float GetHealth() = 0;
private:

};

#endif