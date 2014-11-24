#include "Enemy.h"

Enemy::Enemy( Vec2 a_pPosition, Vec2 a_uiSize, int a_iSpeed, unsigned int a_iSprite, float a_fHealth ): Entity( a_pPosition, a_uiSize, a_iSpeed, a_iSprite, a_fHealth )
{

}
	
void Enemy::OnCollision( int a_iEffect, int a_iModifier )
{
	switch ( a_iEffect )
	{
	case TAKE_DAMAGE_EFFECT:
		m_fHealth -= a_iModifier;
		break;
	case GIVE_HEALTH_EFFECT:
		m_fHealth += a_iModifier;
		break;
	default:
		break;
	}
}