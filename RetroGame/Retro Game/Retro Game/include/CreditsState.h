////////////////////////////////////////////////////////////
// File: CreditsState.h
// Author: Nick Smith
// Date Created: 20th May 2013
// Brief: Credits Screen State
////////////////////////////////////////////////////////////

#ifndef _CREDITS_H_
#define _CREDITS_H_

#include "State.h"

class Sprites;

class CreditsState : public State
{
public:
	CreditsState();
	virtual ~CreditsState();

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

#endif // _CREDITS_H_