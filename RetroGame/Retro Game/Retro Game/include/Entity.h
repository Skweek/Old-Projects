////////////////////////////////////////////////////////////
// File: Entity.h
// Author: Nick Smith
// Date Created: 29th April 2013
// Brief: Base Entity class
////////////////////////////////////////////////////////////

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Vec2.h"
#include "AIE.h"
#include "Enums.h"

class Entity
{
public:
	// Default Constructor
	Entity( Vec2 a_pPosition, Vec2 a_pSize, int a_iSpeed, unsigned int a_iSprite, float a_fHealth );
	virtual ~Entity();

	//+===================================+//
	//	Get/Set information
	//+===================================+//
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
	float m_fHealth;

};

#endif