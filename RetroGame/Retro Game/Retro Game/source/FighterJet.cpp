#include "FighterJet.h"
#include "Level.h"
#include "Timer.h"

FighterJet::FighterJet( Vec2 a_pPosition, Vec2 a_uiSize, int a_iSpeed, unsigned int a_iSprite, float a_fHealth ): Enemy( a_pPosition, a_uiSize, a_iSpeed, a_iSprite, a_fHealth )
{
	m_iSideToFlyTo = RIGHT_DIR;
	m_fBulletInterval = 0.1f;
	m_pBulletTimer = new Timer;

	m_pBulletTimer->Start( m_fBulletInterval );
}

void FighterJet::Update( float a_fDelta, Level* LevelHandle )
{
	m_pBulletTimer->Update();

	Move( m_iSideToFlyTo, a_fDelta );
	Move( DOWN_DIR, a_fDelta );
	
	if ( m_pPosition.m_fX > 600.f )
	{
		m_iSideToFlyTo = LEFT_DIR;
	}
	else if ( m_pPosition.m_fX < 30.f )
	{
		m_iSideToFlyTo = RIGHT_DIR;
	}

	if ( m_pBulletTimer->m_bTimerFinished )
	{
		m_pBulletTimer->Reset();
		LevelHandle->ShootBullet( m_pPosition + Vec2( m_pSize.m_fX / 2, 64.f ), 5, DOWN_DIR );
	}

	Draw();
}

float FighterJet::GetHealth()
{
	return m_fHealth;
}