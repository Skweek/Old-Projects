#include "AIBehaviours.h"


Vec2 AlignWith( Vec2 a_pTarget ) // Travels in the same direction as something
{
	// Normalises the normalised target velocity
	return a_pTarget.NormaliseVec2();
}

Vec2 FollowTarget( Vec2 a_pTarget, Vec2 a_pSelf ) // Moves towards an object
{
	// Get the difference between the two vectors
	Vec2 pResult = a_pTarget - a_pSelf;
	// return this vec2 normalised
	return pResult.NormaliseVec2();
}

Vec2 AvoidTarget( Vec2 a_pTarget, Vec2 a_pSelf ) // Moves away from an object
{
	// Get the difference between the two vectors
	Vec2 pResult = a_pTarget - a_pSelf;
	// Negate the vector to reverse the direction
	pResult *= -1;
	// return this vec2 normalised
	return pResult.NormaliseVec2();
}