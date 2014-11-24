////////////////////////////////////////////////////////////
// File: GameState.h
// Author: Nick Smith
// Date Created: 15th May 2013
// Brief: Game State
////////////////////////////////////////////////////////////

#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "State.h"

class Player;

class GameState : public State
{
public:
	GameState();
	virtual ~GameState();

	//+===================================+//
	//	Virtual functions for states
	//+===================================+//
	virtual void	InitState();
	virtual void	UpdateState( float a_fDelta, int* a_iKeys );
	virtual void	LeaveState();

private:
	Player* m_pPlayer;
};

#endif // _GAME_STATE_H_