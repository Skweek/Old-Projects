////////////////////////////////////////////////////////////
// File: GameEnd.h
// Author: Nick Smith
// Date Created: 15th May 2013
// Brief: Game Over State
////////////////////////////////////////////////////////////

#ifndef _GAME_END_H_
#define _GAME_END_H_

#include "State.h"

class GameOver : public State
{
public:
	GameOver();
	virtual ~GameOver();

	//+===================================+//
	//	Virtual functions for states
	//+===================================+//
	virtual void	InitState();
	virtual void	UpdateState( float a_fDelta );
	virtual void	LeaveState();

private:

};

#endif // _GAME_END_H_