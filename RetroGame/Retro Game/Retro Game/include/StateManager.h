////////////////////////////////////////////////////////////
// File: StateManager.h
// Author: Nick Smith
// Date Created: 15th May 2013
// Brief: State manager
////////////////////////////////////////////////////////////

#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

#pragma warning (disable:4996)

#include "AIE.h"
#include "Vec2.h"

class State;
class InputHandler;
class Sprites;

class StateManager
{
public:
	//+===================================+//
	//	Singleton design as we only need one
	//	statemanager
	//+===================================+//
	static StateManager*	CreateInstance();
	static StateManager*	GetInstance();

	static void				DestroyInstance();

	~StateManager();

	//+===================================+//
	//	virtual incase of derivation from
	//	this class, this is good practice
	//	apparently.
	//+===================================+//
	virtual void			Init();
	virtual void			EnterState( int a_iStateName );
	
			void			Update();

			State*			GetCurrentState();	
			State*			GetPreviousState();	

	//+===================================+//
	//	Stores key presses for access to
	//	all states
	//+===================================+//
	bool* KeysList;

	//+===================================+//
	//	Gets window and map sizes 
	//	returns vec2
	//+===================================+//
	Vec2 GetWindowSize();
	Vec2 GetMapSize();

private:
	//+===================================+//
	//	Constructors are private to prevent
	// more than one instance accidentally 
	// being created
	//+===================================+//
	StateManager();

	//+===================================+//
	//	Static pointer to instance
	//+===================================+//
	static StateManager* m_pStateManager;
	State* m_pCurrentState;
	State* m_pPreviousState;

	//+===================================+//
	//	Total Game time and time sonce last frame
	//+===================================+//	
	float m_fGameTime;
	float m_fTimeSinceLastFrame;

	//+===================================+//
	//	Check to make sure game should
	//	Actually be doing things
	//+===================================+//	
	bool m_bRunning;

	//+===================================+//
	//	Pointer to Input Handler
	//	Pointer to Sprites
	//+===================================+//	
	InputHandler* Input;
	Sprites* SpriteList;

};

#endif // _STATEMANAGER_H_