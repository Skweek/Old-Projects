////////////////////////////////////////////////////////////
// File: HighScoresState.h
// Author: Nick Smith
// Date Created: 20th May 2013
// Brief: High Scores State
////////////////////////////////////////////////////////////

#ifndef _HIGHSCORES_H_
#define _HIGHSCORES_H_

#include "State.h"

class Sprites;

class HighScoresState : public State
{
public:
	HighScoresState();
	virtual ~HighScoresState();

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

#endif // _HIGHSCORES_H_