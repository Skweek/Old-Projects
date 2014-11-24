////////////////////////////////////////////////////////////
// File: StateManager.h
// Author: Nick Smith
// Date Created: 15th July 2013
// Brief: State manager
////////////////////////////////////////////////////////////

#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

#include "Util.h"

class State;

class StateManager
{
public:
	//+===================================+//
	//	Singleton design as we only need one
	//	statemanager
	//+===================================+//
	static StateManager*	Create();
	static StateManager*	Get();

	static void				Destroy();

	~StateManager();

	//+===================================+//
	//	virtual incase of derivation from
	//	this class, this is good practice
	//	apparently.
	//+===================================+//
	virtual void			Init();
	virtual void			EnterState( int a_iStateName );
	
			void			LoadResources();
			void				Update();

			State*			GetCurrentState();	
			State*			GetPreviousState();	

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
	//	Total Game time and time since last frame
	//+===================================+//	
	float m_fGameTime;
	float m_fTimeSinceLastFrame;

	//+===================================+//
	//	Check to make sure game should
	//	Actually be doing things
	//+===================================+//	
	bool m_bRunning;

	//+===================================+//
	//	Key press list
	//+===================================+//	
	int* m_iKeyList;

	//+===================================+//
	//	Window Setup variables
	//+===================================+//	
	int InitialWindow;
	Vec2 m_pWindowSize;
	const char* m_ccWindowTitle;

	//+===================================+//
	//	Arrays to store IDs of objects
	//	Pretty much always going to be intss
	//+===================================+//	
	int Layouts[10]; 
	int Maps[10];		// Create .ini file to get this information from
	int Sprites[100];	// these are just maximum values and is a bit wasteful
	int Fonts[5];		// Also need to create enums or something to that
	int MapObjects;		// effect to better keep track of them

	//+===================================+//
	//	UI element linked functions
	//+===================================+//
	void MainMenu();
	void NewGame();
	void Quit();

};

#endif // _STATEMANAGER_H_