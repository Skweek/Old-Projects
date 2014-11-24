////////////////////////////////////////////////////////////
// File: InputHandler.h
// Author: Nick Smith
// Date Created: 16th April 2013
// Brief: Input handler
////////////////////////////////////////////////////////////

#ifndef _INPUT_H_
#define _INPUT_H_

#include "Keys.h"

class Game;

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	//+===================================+//
	//	Singleton design as we only need one
	//	input handle
	//+===================================+//
	static InputHandler*	CreateInstance();
	static InputHandler*	GetInstance();

	static void	DestroyInstance();

	void Update( float a_fDelta );

	//+===================================+//
	//	Used to get input for states
	//+===================================+//
	bool* GetKeyList();
	
private:
	float m_fLastKeyPressTime;
	Keys* KeyList;

	//+===================================+//
	//	Static pointer to instance
	//+===================================+//
	static InputHandler* m_pInputHandler;


};

#endif