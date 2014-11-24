////////////////////////////////////////////////////////////
// File: MediaPlayer.h
// Author: Nick Smith
// Date Created: 15th May 2013
// Brief: Game State
////////////////////////////////////////////////////////////

#ifndef _MEDIA_PLAYER_H
#define _MEDIA_PLAYER_H

#include "State.h"

class MediaPlayer : public State
{
public:
	MediaPlayer();
	virtual ~MediaPlayer();

	//+===================================+//
	//	Virtual functions for states
	//+===================================+//
	virtual void	InitState();
	virtual void	UpdateState( float a_fDelta, int* a_iKeys );
	virtual void	LeaveState();

private:
	float* spec;
	Vec2* LineEnds;
};

#endif // _MEDIA_PLAYER_H