////////////////////////////////////////////////////////////
// File: Collision.h
// Author: Nick Smith
// Date Created: 16th July 2013
// Brief: Collision Handling
////////////////////////////////////////////////////////////

#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Utilities.h"

bool RayCollision( Vec2 a_pStart, Vec2 a_pEnd );
int BoxCollision( Vec2 a_pSize1, Vec2 a_pPos1, Vec2 a_pSize2, Vec2 a_pPos2 );
bool LineIntersection( Vec2 a_pV1, Vec2 a_pV2, Vec2 a_pV3, Vec2 a_pV4 );

#endif //_COLLISION_H_