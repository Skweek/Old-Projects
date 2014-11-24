#include "Player.h"
#include "Level.h"
#include "Timer.h"

Player::Player( Vec2 a_pPosition, Vec2 a_uiSize, int a_iSpeed, unsigned int a_iSprite, float a_fHealth ): Entity( a_pPosition, a_uiSize, a_iSpeed, a_iSprite,a_fHealth )
{
	m_bCanMoveLeft = true;
	m_bCanMoveRight = true;
	m_bCanMoveUp = true;
	m_bCanMoveDown = true;
		
	m_fLives = 3;

	m_fBulletInterval = 0.1f;
	m_pBulletTimer = new Timer;

	m_pBulletTimer->Start( m_fBulletInterval );
}

void Player::Update( float a_fDelta, Level* LevelHandle, bool* a_iKeys )
{
	m_pBulletTimer->Update();

	for ( int i = 0; i < KEY_LAST; ++i )
	{
		if ( a_iKeys[i] == true )
		{
			switch( i )
			{
			case KEY_UP:
				if( m_bCanMoveUp )
				{
					Move( UP_DIR, a_fDelta );
				}
				break;
			case KEY_DOWN:
				if( m_bCanMoveDown )
				{
					Move( DOWN_DIR, a_fDelta );
				}
				break;
			case KEY_LEFT:
				if( m_bCanMoveLeft )
				{
					Move( LEFT_DIR, a_fDelta );
				}
				break;
			case KEY_RIGHT:
				if( m_bCanMoveRight )
				{
					Move( RIGHT_DIR, a_fDelta );
				}
				break;
			case KEY_SPACE:
				if ( m_pBulletTimer->m_bTimerFinished )
				{
					m_pBulletTimer->Reset();
					LevelHandle->ShootBullet( Vec2( m_pPosition.m_fX + ( m_pSize.m_fX / 2 ), m_pPosition.m_fY - 32.f ), 30, 3 );
				}
				break;
			default:
				break;
			}
		}
	}

	if( m_fHealth <= 0.f )
	{
		--m_fLives;
		m_fHealth = 100.f;
		m_pPosition = Vec2( 200.f, 600.f );
	}
}
	
void Player::OnCollision( int a_iEffect, int a_iModifier )
{
	switch ( a_iEffect )
	{
	case TAKE_DAMAGE_EFFECT:
		m_fHealth -= a_iModifier;
		break;
	case GIVE_HEALTH_EFFECT:
		m_fHealth += a_iModifier;
		break;
	case STOP_MOVEMENT_EFFECT:
		switch ( a_iModifier )
		{
		case LEFT_DIR:
			m_bCanMoveLeft = false;
			break;
		case RIGHT_DIR:
			m_bCanMoveRight = false;
			break;
		case UP_DIR:
			m_bCanMoveUp = false;
			break;
		case DOWN_DIR:
			m_bCanMoveDown = false;
			break;
		default:
			m_bCanMoveDown = true;
			m_bCanMoveUp = true;
			m_bCanMoveRight = true;
			m_bCanMoveLeft = true;
			break;
		}
		break;
	default:
		break;
	}
}

float Player::GetHealth()
{
	return m_fHealth;
}

float Player::GetLives()
{
	return m_fLives;
}