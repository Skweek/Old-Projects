#include "Player.h"

Player::Player( const char* a_ccActorFile, Vec2 a_pSize, Vec2 a_pPos )
{
	m_iSprite = CreateNewActor( a_ccActorFile, a_pPos );
	m_pPos = a_pPos;
	m_pSize = a_pSize;

	m_fXSpeed = 0;
	m_fYSpeed = 0;

	m_bOnGround = false;
	m_pCurrentPath = new Vec2();
	m_pCurrentPath->m_fX = -1;
	m_pFollowing = nullptr;
	m_pAvoiding = nullptr;
	m_bWandering = false;
	m_bFollowingClosest = false;
}

Player::~Player()
{
	delete m_pCurrentPath;
	delete m_pFollowing;
	delete m_pAvoiding;
}

void Player::SetPath( Vec2 a_pStart, Vec2 a_pEnd )
{
	m_pCurrentPath = NULL;
	int iCount = 0;
	float** tempPath = FindPath( a_pStart, a_pEnd );
	while( tempPath[iCount][0] != -1 )
	{
		++iCount;
	}
	m_iPathLength = iCount;
	m_pCurrentPath = new Vec2[iCount];
	for( int i = 0; i < iCount; ++i )
	{
		m_pCurrentPath[i] = Vec2( tempPath[i][0], tempPath[i][1] );
	}
}

void Player::Follow( Player* a_pPlayerToFollow )
{
	m_pFollowing = a_pPlayerToFollow;
}

void Player::SetTargetsToFollow( std::vector<Vec2> a_pTargets )
{	
	m_bFollowingClosest = true;
	m_pTargetsToFollow = a_pTargets;
}

Vec2 Player::FindClosest()
{
	std::vector<float*> pfTargets;
	for( int i = 0; i < (int)m_pTargetsToFollow.size(); ++i )
	{
		pfTargets.push_back( m_pTargetsToFollow[i] );
	}

	Vec2 p = Vec2( FindClosestObject( m_pPos, pfTargets ) );
	return p;
}

void Player::Wander( bool a_bWander )
{
	m_bWandering = a_bWander;
}

void Player::Avoid( Player* a_pPlayerToAvoid )
{
	m_pAvoiding = a_pPlayerToAvoid;
}

bool Player::MoveTowards( float a_fDelta, Vec2 a_pDestination )
{
	// Get the directions we need to head
	float XDir = m_pPos[0] - a_pDestination[0];
	float YDir = m_pPos[1] - a_pDestination[1];
	if( XDir > 0 )
	{
		XDir = -1;
	}
	else if( XDir < 0 )
	{
		XDir = 1;
	}
	else
	{
		XDir = 0;
	}

	if( YDir > 0 )
	{
		YDir = -1;
	}
	else if( YDir < 0 )
	{
		YDir = 1;
	}
	else
	{
		YDir = 0;
	}

	m_fXSpeed = XDir;
	m_fYSpeed = YDir;

	m_pPos += Vec2( m_fXSpeed, m_fYSpeed );
	MoveActor( m_iSprite, m_pPos );

	if( m_pPos == a_pDestination )
	{
		return true;
	}
	return false;
}

void Player::Update( float a_fDelta, int* a_iKeys )
{
	///////////////////////////////////////////////////////////////////
	// Put collision testing back in here once it has been re-written//
	///////////////////////////////////////////////////////////////////

	if( m_bWandering )
	{
		Vec2 pNewVelocity = Vec2( WanderAround( m_pPos ) );
		m_pPos += Vec2( pNewVelocity[0], pNewVelocity[1] );

		MoveActor( m_iSprite, m_pPos );
	}

	// Are we just aiming for our closest thing?
	else if( m_bFollowingClosest )
	{
		Vec2 pTarget = FindClosest();
		Vec2 pNewVelocity = Vec2( FollowATarget( pTarget, m_pPos ) );
		m_pPos += Vec2( pNewVelocity[0], pNewVelocity[1] );

		MoveActor( m_iSprite, m_pPos );
	}

	// If we have a path for this player then use it to move instead of accepting input
	else if( m_pCurrentPath->m_fX != -1 )
	{
		static int it = 0;
		static int iDirToTravel = 1;
		if( MoveTowards( a_fDelta, ( m_pCurrentPath[it] + Vec2( m_pSize[0] / 2, 0.f ) ) ) )
		{
			it += iDirToTravel;
		}

		if( it >= m_iPathLength - 1 )
		{
			//it = 0;
			iDirToTravel = -1;
		}

		if( it <= 0 )
		{
			iDirToTravel = 1;
		}

		for( int i = 0; i < m_iPathLength; ++i )
		{
			if( i != m_iPathLength - 1 )
			{	
				DrawLine( m_pCurrentPath[i], m_pCurrentPath[i+1], Vec4( 0.7f, 0.4f, 0.3f, 1.f ) );
			}
		}
		
	}

	// are we meant to be following another object? lets follow them
	else if( m_pFollowing != nullptr )
	{
		Vec2 pNewVelocity = Vec2( FollowATarget( m_pFollowing->m_pPos, m_pPos ) );
		m_pPos += Vec2( pNewVelocity[0], pNewVelocity[1] );

		MoveActor( m_iSprite, m_pPos );
	}

	// Are we meant to be avoiding something? Move away from it
	else if( m_pAvoiding != nullptr )
	{
		Vec2 pNewVelocity;
		if( ( m_pPos - m_pAvoiding->m_pPos ).GetMagnitude() < 100 )
		{
			pNewVelocity = Vec2( AvoidATarget( m_pAvoiding->m_pPos, m_pPos ) );
		}

		m_pPos += Vec2( pNewVelocity[0], pNewVelocity[1] );

		MoveActor( m_iSprite, m_pPos );
	}

	else // Input controlled
	{
		if( a_iKeys[m_iKeyLeft] == 1 )
		{
			if( m_bCanMoveLeft )
			{
				m_fXSpeed = -30.f * a_fDelta;
				TurnActor( m_iSprite, 2 );
			}
		}

		if( a_iKeys[m_iKeyRight] )
		{
			if( m_bCanMoveRight )
			{
				m_fXSpeed = 30.f * a_fDelta;
				TurnActor( m_iSprite, 3 );
			}
		}

		if( a_iKeys[m_iKeyUp] == 1 )
		{
			if( m_bCanMoveLeft )
			{
				m_fYSpeed = -30.f * a_fDelta;
				TurnActor( m_iSprite, 4 );
			}
		}

		if( a_iKeys[m_iKeyDown] )
		{
			if( m_bCanMoveRight )
			{
				m_fYSpeed = 30.f * a_fDelta;
				TurnActor( m_iSprite, 1 );
			}
		}


		if ( a_iKeys[m_iKeyLeft] == KEY_IS_UP && a_iKeys[m_iKeyRight] == KEY_IS_UP ) 
		{ 
			if ( m_fXSpeed > 0.05f ) 
			{                
				m_fXSpeed -= 0.05f; 
			} 
  
			else if ( m_fXSpeed < -0.05f ) 
			{                
				m_fXSpeed += 0.05f; 
			} 
			else if ( m_fXSpeed < 0.05f || m_fXSpeed > -0.05f ) 
			{ 
				m_fXSpeed = 0.f; 
			} 
		} 

		if ( a_iKeys[m_iKeyUp] == KEY_IS_UP && a_iKeys[m_iKeyDown] == KEY_IS_UP ) 
		{ 
			if ( m_fYSpeed > 0.05f ) 
			{                
				m_fYSpeed -= 0.05f; 
			} 
  
			else if ( m_fYSpeed < -0.05f ) 
			{                
				m_fYSpeed += 0.05f; 
			} 
			else if ( m_fYSpeed < 0.05f || m_fYSpeed > -0.05f ) 
			{ 
				m_fYSpeed = 0.f; 
			} 
		} 

		m_pPos += Vec2( m_fXSpeed, m_fYSpeed );

		MoveActor( m_iSprite, m_pPos );
	}

}

void Player::Draw()
{	
	DrawActor( m_iSprite );
}

void Player::SetKeys( int a_iUp, int a_iDown, int a_iLeft, int a_iRight )
{
	m_iKeyUp = a_iUp;
	m_iKeyDown = a_iDown;
	m_iKeyLeft = a_iLeft;
	m_iKeyRight = a_iRight;
}