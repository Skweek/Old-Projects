////////////////////////////////////////////////////////////
// File: Player.h
// Author: Nick Smith
// Date Created: 16th May 2013
// Brief: Player Class	
////////////////////////////////////////////////////////////

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Util.h"

class Player
{
public:
	Player( const char* a_ccAnimationFile, Vec2 a_pSize, Vec2 a_pPos );
	~Player();

	void Update( float a_fDelta, int* a_iKeys );
	void Draw();
	void SetKeys( int a_fUp, int a_fDown, int a_fLeft, int a_fRight );

	void SetPath( Vec2 a_pStart, Vec2 a_pEnd );
	void SetTargetsToFollow( std::vector<Vec2> a_pTargets );
	Vec2 FindClosest();
	bool MoveTowards( float a_fDelta, Vec2 a_pDestination );
	void Follow( Player* a_pPlayerToFollow );
	void Avoid( Player* a_pPlayerToAvoid );
	void Wander( bool a_bWander );

	inline int GetSprite()
	{
		return m_iSprite;
	}

	inline float GetMomentum()
	{
		return m_fXSpeed;
	}

	inline void Push( float x )
	{
		m_pPos[0] += x;
	}

	inline Vec2 GetPos()
	{
		return m_pPos;
	}

private:
	Vec2 m_pPos;
	Vec2 m_pSize;

	float m_fXSpeed;
	float m_fYSpeed;

	bool m_bOnGround;
	bool m_bCanMoveLeft;
	bool m_bCanMoveRight;

	int m_iSprite;

	int m_iKeyUp;
	int m_iKeyDown;
	int m_iKeyLeft;
	int m_iKeyRight;

	Vec2* m_pCurrentPath;
	int m_iPathLength;

	Vec2 m_pCurrentDestination;

	Player* m_pFollowing;	// This needs to be changed
	Player* m_pAvoiding;	// to entity when I have changed everything
	bool m_bWandering;		// to be inherited from a base entity class
	bool m_bFollowingClosest;
	std::vector<Vec2> m_pTargetsToFollow;

};

#endif // _PLAYER_H_