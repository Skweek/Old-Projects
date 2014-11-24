#include "Collision.h"

#include "Window.h"
#include "MapManager.h"

#include "Shapes.h" // For collsion hit boxes

bool RayCollision( Vec2 a_pStart, Vec2 a_pEnd )
{
	a_pStart;
	a_pEnd;
	return true;
}

int BoxCollision( Vec2 a_pSize1, Vec2 a_pPos1, Vec2 a_pSize2, Vec2 a_pPos2 )
{
	// Get the box lines for the objects
	float pX = a_pPos1.m_fX;
	float pY = a_pPos1.m_fY;
	float pW = a_pSize1.m_fX;
	float pH = a_pSize1.m_fY;

	float eX = a_pPos2.m_fX;
	float eY = a_pPos2.m_fY;
	float eW = a_pSize2.m_fX;
	float eH = a_pSize2.m_fY;
		 
	Vec2 pTopLeft1 = Vec2( pX - ( pW /2 ), pY  - ( pH /2 ) );
	Vec2 pTopRight1 = Vec2( pX + ( pW /2 ), pY  - ( pH /2 ) );
	Vec2 pBottomLeft1 = Vec2( pX - ( pW /2 ), pY  + ( pH /2 ) );
	Vec2 pBottomRight1 = Vec2( pX + ( pW /2 ), pY  + ( pH /2 ) );
	
	Vec2 pTopLeft2 = Vec2( eX, eY );
	Vec2 pTopRight2 = Vec2( (eX + eW), eY );
	Vec2 pBottomLeft2 = Vec2( eX, (eY + eH) );
	Vec2 pBottomRight2 = Vec2( (eX + eW) , (eY + eH) );

	// Debug info - Hit Boxes
	if( bDebugInfo )
	{
		Shapes::Get()->DrawLine( pTopLeft1, pTopRight1, Vec4(1,1,1,1) );
		Shapes::Get()->DrawLine( pTopLeft1, pBottomLeft1, Vec4(1,1,1,1) );
		Shapes::Get()->DrawLine( pTopRight1, pBottomRight1, Vec4(1,1,1,1) );
		Shapes::Get()->DrawLine( pBottomRight1, pBottomLeft1, Vec4(1,1,1,1) );

		Shapes::Get()->DrawLine( pTopLeft2, pTopRight2 );
		Shapes::Get()->DrawLine( pTopLeft2, pBottomLeft2 );
		Shapes::Get()->DrawLine( pTopRight2, pBottomRight2 );
		Shapes::Get()->DrawLine( pBottomRight2, pBottomLeft2 );
	}
		
	if( LineIntersection( pBottomLeft1, pBottomRight1, pTopLeft2, pTopRight2 ) )
	{
		return COLLIDE_DOWN;
	}		
	else if( LineIntersection( pTopLeft1, pTopRight1, pBottomLeft2, pBottomRight2 ) )
	{
		return COLLIDE_UP;
	}		
	else if( LineIntersection( pTopLeft1, pBottomLeft1, pTopRight2, pBottomRight2 ) )
	{
		return COLLIDE_LEFT;
	}		
	else if( LineIntersection( pTopRight1, pBottomRight1, pTopLeft2, pBottomLeft2 ) )
	{
		return COLLIDE_RIGHT;
	}

	return NO_COLLISION; // No collision
}

bool LineIntersection( Vec2 a_pV1, Vec2 a_pV2, Vec2 a_pV3, Vec2 a_pV4 )
{
	float intersection = ( ( a_pV1.m_fX - a_pV2.m_fX ) * ( a_pV3.m_fY - a_pV4.m_fY ) - 
						 ( a_pV1.m_fY - a_pV2.m_fY ) * ( a_pV3.m_fX - a_pV4.m_fX ) );

	if( a_pV1.m_fY < a_pV3.m_fY + 3.5f && a_pV1.m_fY > a_pV3.m_fY - 3.5f )
	{
		if( a_pV1.m_fX < a_pV4.m_fX + 3.5f && a_pV1.m_fX > a_pV3.m_fX - 3.5f )
		{
			return true;
		}
		else if( a_pV2.m_fX < a_pV4.m_fX + 3.5f && a_pV2.m_fX > a_pV3.m_fX - 3.5f )
		{
			return true;
		}
	}

	//// Full check for intersection
	//float pre = (a_pV1.m_fX*a_pV2.m_fY - a_pV1.m_fY*a_pV2.m_fX), post = (a_pV3.m_fX*a_pV4.m_fY - a_pV3.m_fY*a_pV4.m_fX);
	//float x = ( pre * (a_pV3.m_fX - a_pV4.m_fX) - (a_pV1.m_fX - a_pV2.m_fX) * post ) / intersection;
	//float y = ( pre * (a_pV3.m_fY - a_pV4.m_fY) - (a_pV1.m_fY - a_pV2.m_fY) * post ) / intersection;
 //
	//if ( x < std::min(a_pV1.m_fX, a_pV2.m_fX) || x > std::max(a_pV1.m_fX, a_pV2.m_fX) ||
	//x < std::min(a_pV3.m_fX, a_pV4.m_fX) || x > std::max(a_pV3.m_fX, a_pV4.m_fX) ) return false; // No Intersection
	//if ( y < std::min(a_pV1.m_fY, a_pV2.m_fY) || y > std::max(a_pV1.m_fY, a_pV2.m_fY) ||
	//y < std::min(a_pV3.m_fY, a_pV4.m_fY) || y > std::max(a_pV3.m_fY, a_pV4.m_fY) ) return false; // No Intersection

	return true; // Intersection

}