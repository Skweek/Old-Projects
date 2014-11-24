////////////////////////////////////////////////////////////
// File: MainMenu.h
// Author: Nick Smith
// Date Created: 15th May 2013
// Brief: Main Menu State
////////////////////////////////////////////////////////////

#ifndef _MAINMENU_H_
#define _MAINMENU_H_

#include "State.h"

class Sprites;

class MainMenu : public State
{
public:
	//+===================================+//
	//	Constructor
	//+===================================+//
	MainMenu();
	virtual ~MainMenu();

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

#endif // _MAINMENUEN_H_