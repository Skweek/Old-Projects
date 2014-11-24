////////////////////////////////////////////////////////////
// File: Keys.h
// Author: Nick Smith
// Date Created: 16th April 2013
// Brief: Struct to hold information about key presses
////////////////////////////////////////////////////////////

#ifndef _KEYS_H_
#define _KEYS_H_

#include "AIE.h"

struct Keys
{
public:
	Keys()
	{		
		for (  int i = 0; i < KEY_LAST; ++i )
		{
			m_bPressed = false;
			m_bKeyUp = false;
		}
	}
	bool m_bPressed;
	bool m_bKeyUp;

};

#endif