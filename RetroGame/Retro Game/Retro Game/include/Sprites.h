////////////////////////////////////////////////////////////
// File: Sprites.h
// Author: Nick Smith
// Date Created: 29th April 2013
// Brief: Globalb Sprites List
////////////////////////////////////////////////////////////

#ifndef _SPRITES_H_
#define _SPRITES_H_

#include "AIE.h"
#include "Enums.h"

extern const int m_iScreenHeight;
extern const int m_iScreenWidth;
	 
extern const int m_iMapHeight;
extern const int m_iMapWidth;

class Sprites
{
public:
	//+===================================+//
	//	Singleton design as we only need one
	//	statemanager
	//+===================================+//
	static Sprites*	CreateInstance();
	static Sprites*	GetInstance();

	static void		DestroyInstance();


	unsigned int GetSprite( int a_iSpriteID );
		
private:	
	Sprites();
	void LoadSprites();
	unsigned int SpritesList[SPRITE_COUNT];

	//+===================================+//
	//	Static pointer to instance
	//+===================================+//
	static Sprites* m_pSpriteList;

};

#endif // _SPRITES_H_