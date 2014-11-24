////////////////////////////////////////////////////////////
// File: AIBehaviours.h
// Author: Nick Smith
// Date Created: 26th August 2013
// Brief: Collection of standard AI behaviours
////////////////////////////////////////////////////////////

#ifndef _AI_BEHAVIOUR_
#define _AI_BEHAVIOUR_

#include "Utilities.h"

// These functions return a vec2 that is the velocity an object should be moving in
Vec2 AlignWith( Vec2 a_pTarget ); // Travels in the same direction as something
Vec2 FollowTarget( Vec2 a_pTarget, Vec2 a_pSelf ); // Moves towards an object
Vec2 AvoidTarget( Vec2 a_pTarget, Vec2 a_pSelf ); // Moves away from an object

#endif // _AI_BEHAVIOUR_