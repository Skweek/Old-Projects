////////////////////////////////////////////////////////////
// File: State.h
// Author: Nick Smith
// Date Created: 15th May 2013
// Brief: Base State class
////////////////////////////////////////////////////////////

#ifndef _STATE_H_
#define _STATE_H_

#include "Util.h"

class State
{
public:
	//+===================================+//
	//	Constructors
	//+===================================+//
	State();
	virtual ~State();

	//+===================================+//
	//	Virtual functions
	//+===================================+//
	virtual void	InitState()						= 0;
	virtual void	UpdateState( float a_fDelta, int* a_iKeys )	= 0;
	virtual void	LeaveState()					= 0;

protected:


};

#endif // _STATE_H_