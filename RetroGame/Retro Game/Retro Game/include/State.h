////////////////////////////////////////////////////////////
// File: State.h
// Author: Nick Smith
// Date Created: 15th May 2013
// Brief: Base State class
////////////////////////////////////////////////////////////

#ifndef _STATE_H_
#define _STATE_H_

#include "Enums.h"
#include <vector>
#include "Vec2.h"

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
	virtual void	UpdateState( float a_fDelta )	= 0;
	virtual void	LeaveState()					= 0;

	int m_iFinalScore;
	bool m_bLevelSuccess;

	std::vector<int> KeyPresses;
protected:
	//+===================================+//
	//	Storage for key list
	//+===================================+//
	bool* KeyList;

};

#endif // _STATE_H_