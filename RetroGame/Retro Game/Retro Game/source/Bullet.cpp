#include "Bullet.h"

Bullet::Bullet( Vec2 a_pPosition, int a_iDamage, int a_iDir, unsigned int a_iSprite, Vec2 a_uiSize, int a_iSpeed ): Entity( a_pPosition, a_uiSize, a_iSpeed, a_iSprite, 1.f )
{
	m_iDamage = a_iDamage;
	m_iDir = a_iDir;
}

Bullet::~Bullet()
{

}

void Bullet::Update( float a_fDelta )
{	
	Move( m_iDir, a_fDelta );
	Draw();
}

int Bullet::GetDirection()
{
	return m_iDir;
}

int Bullet::GetDamage()
{
	return m_iDamage;
}