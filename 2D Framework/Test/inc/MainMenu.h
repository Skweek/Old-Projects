////////////////////////////////////////////////////////////
// File: MainMenu.h
// Author: Nick Smith
// Date Created: 15th May 2013
// Brief: Main Menu State
////////////////////////////////////////////////////////////

#ifndef _MAINMENU_H_
#define _MAINMENU_H_

#include "State.h"

class Menu : public State
{
public:
	//+===================================+//
	//	Constructor
	//+===================================+//
	Menu();
	virtual ~Menu();

	//+===================================+//
	//	Virtual functions for states
	//+===================================+//
	virtual void	InitState();
	virtual void	UpdateState( float a_fDelta, int* a_iKeys );
	virtual void	LeaveState();

private:

};

#endif // _MAINMENUEN_H_