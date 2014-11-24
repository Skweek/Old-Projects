////////////////////////////////////////////////////////////
// File: WindowShapes.h
// Author: Nick Smith
// Date Created: 29th May 2013
// Brief: Collection of window shape points
////////////////////////////////////////////////////////////

#ifndef _WINDOW_SHAPES_
#define _WINDOW_SHAPES_

Vec2 SquareWindow[4] = 
{
	Vec2( 0.f, 0.f ), 
	Vec2( 1.f, 0.f ), 
	Vec2( 1.f, 1.f ), 
	Vec2( 0.f, 1.f )
};

Vec2 TriangleWindow[3] = 
{
	Vec2( 0.5f, 0.f ),
	Vec2( 0.f, 1.f ),
	Vec2( 1.f, 1.f ) 
};

// const float* CircleWindow[0] = 
// {
//		This will require me to add some extra
//		functions to glfw, really can't be bothered right now
//		Could also just modify the current function to take a
//		parameter to determine if the shape is an ellipse
//		or a polygon.
// };

Vec2 ZWindow[10] = 
{
	Vec2( 0.f,	0.f ),		// 1
	Vec2( 1.f,	0.f ),		// 2
	Vec2( 1.f,	0.1f ),		// 3
	Vec2( 0.1f, 0.9f ),		// 4
	Vec2( 1.f,	0.9f ),		// 5
	Vec2( 1.f,	1.f ),		// 6
	Vec2( 0.f,	1.f ),		// 7
	Vec2( 0.f,	0.9f ),		// 8
	Vec2( 0.9f, 0.1f ),		// 9
	Vec2( 0.f,	0.1f )		// 10
};

#endif // _WINDOW_SHAPES_