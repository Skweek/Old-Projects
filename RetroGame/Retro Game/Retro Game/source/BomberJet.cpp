#include "BomberJet.h"
#include "Level.h"
#include "Timer.h"

BomberJet::BomberJet( Vec2 a_pPosition, Vec2 a_uiSize, int a_iSpeed, unsigned int a_iSprite, float a_fHealth ): Enemy( a_pPosition, a_uiSize, a_iSpeed, a_iSprite, a_fHealth )
{	
	m_fBulletInterval = 1.f;
	m_pBulletTimer = new Timer;

	m_pBulletTimer->Start( m_fBulletInterval );
}

void BomberJet::Update( float a_fDelta, Level* LevelHandle )
{
	m_pBulletTimer->Update();

	Move( DOWN_DIR, a_fDelta );
		
	if ( m_pBulletTimer->m_bTimerFinished )
	{
		m_pBulletTimer->Reset();
		LevelHandle->ShootBullet( m_pPosition + Vec2( m_pSize.m_fX / 2, 64.f ), 10, DOWN_DIR );
	}

	Draw();
}

float BomberJet::GetHealth()
{
	return m_fHealth;
}