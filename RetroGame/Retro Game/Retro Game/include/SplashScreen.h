////////////////////////////////////////////////////////////
// File: SplashScreen.h
// Author: Nick Smith
// Date Created: 15th May 2013
// Brief: Splash Screen State
////////////////////////////////////////////////////////////

#ifndef _SPLASHSCREEN_H_
#define _SPLASHSCREEN_H_

#include "State.h"

class Sprites;

class SplashScreen : public State
{
public:
	SplashScreen();
	virtual ~SplashScreen();

	//+===================================+//
	//	Virtual functions for states
	//+===================================+//
	virtual void	InitState();
	virtual void	UpdateState( float a_fDelta );
	virtual void	LeaveState();

private:
	//+===================================+//
	//	Pointer to Sprites
	//+===================================+//	
	Sprites* SpriteList;
	
};

#endif // _SPLASHSCREEN_H_