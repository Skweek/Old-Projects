////////////////////////////////////////////////////////////
// File: Sprite.h
// Author: Nick Smith
// Date Created: 29th April 2013
// Brief: Base Sprite class
////////////////////////////////////////////////////////////

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Vec2.h"
#include "AIE.h"
#include "Enums.h"

class Sprite
{
public:
	// Default Constructor
	Sprite( Vec2 a_pPosition, Vec2 a_pSize, int a_iSpeed, unsigned int a_iSprite );
	virtual ~Sprite();

	Vec2 GetSize() { return m_pSize; }
	Vec2 GetPos() { return m_pPosition; }
	void SetSize( Vec2 a_pSize );
	void SetPos( Vec2 a_pPosition );

	void Move( int a_iDir, float a_fDelta );

	void Draw();
		
protected:
	Vec2 m_pPosition;
	Vec2 m_pSize;
	float m_fSpeed;
	unsigned int m_uiSprite;

};

#endif