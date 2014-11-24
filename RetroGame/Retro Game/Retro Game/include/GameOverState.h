////////////////////////////////////////////////////////////
// File: GameOverState.h
// Author: Nick Smith
// Date Created: 20th May 2013
// Brief: Game Over Screen
////////////////////////////////////////////////////////////

#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

#include "State.h"

class Sprites;

class GameOverState : public State
{
public:
	GameOverState();
	virtual ~GameOverState();

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

	bool m_bSuccess;
	int m_iScore;
};

#endif // _GAMEOVER_H_