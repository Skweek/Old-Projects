////////////////////////////////////////////////////////////
// File: Turret.h
// Author: Nick Smith
// Date Created: 1st May 2013
// Brief: Turret class
////////////////////////////////////////////////////////////

#ifndef _TURRET_H_
#define _TURRET_H_

#include "Enemy.h"

class Turret : public Enemy
{
public:
	Turret( Vec2 a_pPosition, Vec2 a_uiSize, int a_iSpeed, unsigned int a_iSprite );

	void Update();	

private:
	
};

#endif