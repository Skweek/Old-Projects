#include "Sprite.h"
#include "Enums.h"

Sprite::Sprite( Vec2 a_pPosition, Vec2 a_pSize, int a_iSpeed, unsigned int a_iSprite )
{
	m_pPosition = a_pPosition;
	m_pSize = a_pSize;
	m_fSpeed = a_iSpeed * 150.f;
	m_uiSprite = a_iSprite;
}

Sprite::~Sprite()
{

}

void Sprite::Draw()
{
	MoveSprite( m_uiSprite, m_pPosition );
	DrawSprite( m_uiSprite );
}

void Sprite::Move ( int a_iDir, float a_fDelta )
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

void Sprite::SetSize( Vec2 a_pSize )
{
	m_pSize = a_pSize;
}

void Sprite::SetPos( Vec2 a_pPosition )
{
	m_pPosition = a_pPosition;
}