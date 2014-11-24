////////////////////////////////////////////////////////////
// File: Collision.h
// Author: Nick Smith
// Date Created: 1st May 2013
// Brief: Collision Detection
////////////////////////////////////////////////////////////

#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Vec2.h"
#include <algorithm>
#include "Enums.h"

class Collision
{
public: 
	//+===================================+//
	//	Collision detection functions
	//+===================================+//
	static bool CheckBoxCollision( Vec2 a_pVec1Pos, Vec2 a_pVec1Size, Vec2 a_pVec2Pos, Vec2 a_pVec2Size );
	static int CheckWallCollision( Vec2 a_pPosition, Vec2 a_pScreenSize );

private:
	static bool CheckLineCollision( Vec2 a_pVec1Pos, Vec2 a_pVec1Size, Vec2 a_pVec2Pos, Vec2 a_pVec2Size );

};

#endif