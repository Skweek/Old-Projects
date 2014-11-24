#include "Collision.h"
#include "AIE.h"

bool Collision::CheckBoxCollision( Vec2 a_pVec1Pos, Vec2 a_pVec1Size, Vec2 a_pVec2Pos, Vec2 a_pVec2Size )
{
	// Get the box lines for the objects
	float pX = a_pVec1Pos.m_fX;
	float pY = a_pVec1Pos.m_fY;
	float pH = a_pVec1Size.m_fX;
	float pW = a_pVec1Size.m_fY;

	float eX = a_pVec2Pos.m_fX;
	float eY = a_pVec2Pos.m_fY;
	float eH = a_pVec2Size.m_fX;
	float eW = a_pVec2Size.m_fY;
	
	Vec2 pTopLeft1 = Vec2( pX, pY );
	Vec2 pTopRight1 = Vec2( (pX + pW), pY );
	Vec2 pBottomLeft1 = Vec2( pX, (pY + pH) );
	Vec2 pBottomRight1 = Vec2( (pX + pW) , (pY + pH) );
		 
	Vec2 pTopLeft2 = Vec2( eX, eY );
	Vec2 pTopRight2 = Vec2( (eX + eW), eY );
	Vec2 pBottomLeft2 = Vec2( eX, (eY + eH) );
	Vec2 pBottomRight2 = Vec2( (eX + eW) , (eY + eH) );

	// Check each pair of lines created
	if ( CheckLineCollision( pTopLeft1, pBottomLeft1, pTopRight2, pBottomRight2 )  ||
		 CheckLineCollision( pTopLeft1, pBottomLeft1, pTopLeft2, pBottomLeft2 ) ||
		 CheckLineCollision( pTopLeft1, pBottomLeft1, pBottomLeft2, pBottomRight2 ) ||
		 CheckLineCollision( pTopLeft1, pBottomLeft1, pTopLeft2, pTopRight2 ) ||
		 					 
		 CheckLineCollision( pTopRight1, pBottomRight1, pTopRight2, pBottomRight2 )  ||
		 CheckLineCollision( pTopRight1, pBottomRight1, pTopLeft2, pBottomLeft2 )  ||
		 CheckLineCollision( pTopRight1, pBottomRight1, pBottomLeft2, pBottomRight2 )  ||
		 CheckLineCollision( pTopRight1, pBottomRight1, pTopLeft2, pTopRight2 )   ||
		 					 
		 CheckLineCollision( pTopLeft1, pTopRight1, pTopRight2, pBottomRight2 )  ||
		 CheckLineCollision( pTopLeft1, pTopRight1, pTopLeft2, pBottomLeft2 )  ||
		 CheckLineCollision( pTopLeft1, pTopRight1, pBottomLeft2, pBottomRight2 ) ||
		 CheckLineCollision( pTopLeft1, pTopRight1, pTopLeft2, pTopRight2 )  ||
		 					 
		 CheckLineCollision( pBottomLeft1, pBottomRight1, pTopRight2, pBottomRight2 ) ||
		 CheckLineCollision( pBottomLeft1, pBottomRight1, pTopLeft2, pBottomLeft2 ) ||
		 CheckLineCollision( pBottomLeft1, pBottomRight1, pBottomLeft2, pBottomRight2 ) ||
		 CheckLineCollision( pBottomLeft1, pBottomRight1, pTopLeft2, pTopRight2 )) return 1;
							  
	return 0;

}

bool Collision::CheckLineCollision( Vec2 a_pVec1, Vec2 a_pVec2, Vec2 a_pVec3, Vec2 a_pVec4 )
{	
	float intersection = ( ( a_pVec1.m_fX - a_pVec2.m_fX ) * ( a_pVec3.m_fY - a_pVec4.m_fY ) - 
						 ( a_pVec1.m_fY - a_pVec2.m_fY ) * ( a_pVec3.m_fX - a_pVec4.m_fX ) );
	
	if ( intersection == 0.0f )
	{
		return 0; //no intersection
	}

	// Full check for intersection
	float pre = (a_pVec1.m_fX*a_pVec2.m_fY - a_pVec1.m_fY*a_pVec2.m_fX), post = (a_pVec3.m_fX*a_pVec4.m_fY - a_pVec3.m_fY*a_pVec4.m_fX);
	float x = ( pre * (a_pVec3.m_fX - a_pVec4.m_fX) - (a_pVec1.m_fX - a_pVec2.m_fX) * post ) / intersection;
	float y = ( pre * (a_pVec3.m_fY - a_pVec4.m_fY) - (a_pVec1.m_fY - a_pVec2.m_fY) * post ) / intersection;
 
	if ( x < std::min(a_pVec1.m_fX, a_pVec2.m_fX) || x > std::max(a_pVec1.m_fX, a_pVec2.m_fX) ||
	x < std::min(a_pVec3.m_fX, a_pVec4.m_fX) || x > std::max(a_pVec3.m_fX, a_pVec4.m_fX) ) return 0;
	if ( y < std::min(a_pVec1.m_fY, a_pVec2.m_fY) || y > std::max(a_pVec1.m_fY, a_pVec2.m_fY) ||
	y < std::min(a_pVec3.m_fY, a_pVec4.m_fY) || y > std::max(a_pVec3.m_fY, a_pVec4.m_fY) ) return 0;

	return 1;
}

int Collision::CheckWallCollision( Vec2 a_pPosition, Vec2 a_pScreenSize )
{
	if ( a_pPosition.m_fX < 0.f )
	{
		return LEFT_DIR;
	}
	if ( a_pPosition.m_fY < 0.f )
	{
		return UP_DIR;
	}
	if ( a_pPosition.m_fX > ( a_pScreenSize.m_fX - 64.f ) )
	{
		return RIGHT_DIR;
	}
	if ( a_pPosition.m_fY > ( a_pScreenSize.m_fY - 64.f ) )
	{
		return DOWN_DIR;
	}

	return 0; // all good

}