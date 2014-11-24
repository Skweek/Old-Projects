////////////////////////////////////////////////////////////
// File: Util.h
// Author: Nick Smith
// Date Created: 15th July 2013
// Brief: Common utilities
////////////////////////////////////////////////////////////

#ifndef _UTIL_H_
#define _UTIL_H_

#include "Framework.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Maths.h"

#include <cmath>

enum GameStates
{
	EMPTY_STATE,
	SPLASH_SCREEN_STATE,
	MAIN_MENU_STATE,
	GAME_STATE,
	MEDIA_PLAYER,
	END_STATE,

	STATE_COUNT
};

const float GRAVITY = 7.f;

#endif //_UTIL_H_