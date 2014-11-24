#include "Entity.h"
#include "Enums.h"

Entity::Entity( Vec2 a_pPosition, Vec2 a_pSize, int a_iSpeed, unsigned int a_iSprite, float a_fHealth )
{
	m_pPosition = a_pPosition;
	m_pSize = a_pSize;
	m_fSpeed = a_iSpeed * 150.f;
	m_uiSprite = a_iSprite;
	m_fHealth = a_fHealth;
}

Entity::~Entity()
{

}

void Entity::Draw()
{
	MoveSprite( m_uiSprite, m_pPosition );
	DrawSprite( m_uiSprite );

	/* Draws boxes around each entity for debugging collision detection
	DrawLine( m_pPosition.m_fX, m_pPosition.m_fY, m_pPosition.m_fX + (m_pSize.m_fX), m_pPosition.m_fY );
	DrawLine( m_pPosition.m_fX, m_pPosition.m_fY, m_pPosition.m_fX, m_pPosition.m_fY + (m_pSize.m_fY) );
	DrawLine( m_pPosition.m_fX + (m_pSize.m_fX), m_pPosition.m_fY + (m_pSize.m_fY), m_pPosition.m_fX + (m_pSize.m_fX), m_pPosition.m_fY );
	DrawLine( m_pPosition.m_fX + (m_pSize.m_fX), m_pPosition.m_fY + (m_pSize.m_fY), m_pPosition.m_fX, m_pPosition.m_fY + (m_pSize.m_fY) );*/
}

void Entity::Move ( int a_iDir, float a_fDelta )
{
	switch ( a_iDir )
	{
	case DOWN_DIR:
		SetPos( m_pPosition + Vec2 ( 0.f, m_fSpeed * a_fDelta ) );
		break;
	case UP_DIR:
		SetPos( m_pPosition - Vec2 ( 0.f, m_fSpeed * a_fDelta ) );
		break;
	case RIGHT_DIR:
		SetPos( m_pPosition + Vec2 ( a_fDelta * m_fSpeed, 0.f ) );
		break;
	case LEFT_DIR:
		SetPos( m_pPosition - Vec2 ( a_fDelta * m_fSpeed, 0.f ) );
		break;
	default:
		break;

	}
}

void Entity::SetSize( Vec2 a_pSize )
{
	m_pSize = a_pSize;
}

void Entity::SetPos( Vec2 a_pPosition )
{
	m_pPosition = a_pPosition;
}