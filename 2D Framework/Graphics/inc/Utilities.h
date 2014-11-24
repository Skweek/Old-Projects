////////////////////////////////////////////////////////////
// File: Utilites.h
// Author: Nick Smith
// Date Created: 5th May 2013
// Brief: Collection of commonly used things
////////////////////////////////////////////////////////////
#ifndef _UTIL_H_
#define _UTIL_H_

// For rela time actor loading
#include <windows.h>

// For python error handling - courtesy of Jamie
#if defined ( _WIN32 )
#define __func__ __FUNCTION__
#endif


// Global includes
#include <glew.h>
#include <glfw3.h>
#include <FreeImage.h>

#define XML tinyxml2 // Shorthand to make typing things out easier
#include "tinyxml2.h"

#include "Enum.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Matrix4.h"
#include "Maths.h"

// These need to be sorted out so they are only included in files that need them.
#include <string>
#include <queue>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <functional>
#include <tuple>



#pragma warning (disable : 4251)
#pragma warning (disable : 4996) // Removes warning about _s functions
#pragma warning (disable : 4706) // Type casting warnings
#pragma warning (disable : 4127) // Removes warning about Assert

#ifdef _DLL_BUILD_
#define DECLDIR __declspec( dllexport )
#elif _STATIC_BUILD_
#define DECLDIR
#else
#define DECLDIR __declspec( dllimport )
#endif // DECLDIR

// Debug bool
extern bool bDebugInfo;

//+ VV common.cpp functions VV

GLuint LoadTexture(const char* a_szTexture, unsigned int a_uiFormat  = 
					GL_BGRA, unsigned int* a_uiWidth  = nullptr, unsigned int* a_uiHeight  = 
					nullptr, unsigned int* a_uiBPP  = nullptr);

GLuint LoadShaders( const char* a_ccVertexFile, const char* a_ccFragmentFile );

GLEWContext* glewGetContext();

#pragma region Memory Management - TO-DO

//void LogMemory( void* p, char* file, int line );
//void FreeMemory( void *p );
//void CleanupMemory();
//void* New( size_t t, char* File, int Line );
//void Delete ( void *p );

#pragma endregion

#pragma region Error Handling - TO-DO
// To do:
// - Log all errors
// - Ignore errors if possible in Release

#define ASSERT(condition, message) \
    do { \
        if(! (condition)) { \
			static char assertText[256] = "";\
			std::cerr << "Assertion: `" message "`\nFailed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << std::endl; \
					  abort();\
        } \
    } while (false)

void LogError();
void ClearErrors();

#pragma endregion

//+ ^^ common.cpp functions ^^

//+ VV public structs VV

struct Vertex
{
	union
	{
		struct 
		{
			Vec4 Pos;
			Vec2 UV;
		};
		
		struct
		{
			float X, Y, Z, W;
			float U, V;
		};
	};
};

struct FontVertex
{
	union
	{
		struct 
		{
			Vec4 Pos;
			Vec2 UV;
			Vec4 Colour;
		};
		
		struct
		{
			float X, Y, Z, W;
			float U, V;
			float R, G, B, A;
		};
	};
};

struct LineVertex
{
	union
	{
		struct 
		{
			Vec4 Pos;
			Vec4 Colour;
		};
		
		struct
		{
			float X, Y, Z, W;
			float R, G, B, A;
		};
	};
};

struct LineShape
{
	Vec2 Start;
	Vec2 End;
	Vec4 Colour;
};

struct Timer
{
	float End;
	float Current;
	float Interval;

	bool Finished;

	// Start the timer and set the end time
	void Start( float a_fEndTime )
	{
		Finished = false;
		Current = 0.f;
		End = a_fEndTime;
		Interval = 0.01f;
	}

	// Resets the timer time to 0, keeps the end time
	void Reset()
	{
		Current = 0.f;
		Finished = false;
	}

	// Updates the timer time and determines if timer is finished
	void Update()
	{
		Current += Interval;

		if( Current >= End )
		{
			Finished = true;
		}
	}
};

struct Character // Fonts
{
	int id;
	float x;
	float y;
	float width;
	float height;
	float xOffset;
	float yOffset;
	float xAdvance;
	float channel;
};

struct MapLayer
{
	int id;
	const char* mapName;
	int numObjects;
	std::tuple<int, int, Vec3>* Objects;

	std::tuple<int,int,Vec3> GetObject( int a_iObject )
	{
		return Objects[a_iObject];
	}

};

struct MapObject
{
	const char* objectName;
	GLuint objectImage;
	Vec2 size;
	int attribute;
};

struct MapAttribute
{
	int id;
	int effect;
	float value;
};

struct ScreenQuadrant
{
	ScreenQuadrant()
	{

	}

	ScreenQuadrant( int a_iId, Vec2 pos, Vec2 size )
	{
		id = a_iId;
		topLeft = pos;
		topRight = pos + Vec2( size[0], 0 );
		bottomLeft = pos + Vec2( 0, size[1] );
		bottomRight = pos + size;
	}

	int id;
	Vec2 topLeft;
	Vec2 topRight;
	Vec2 bottomLeft;
	Vec2 bottomRight;
};

//+ ^^ public structs ^^



enum UIButtonState
{
	UI_BUTTON_UP,
	UI_BUTTON_DOWN
};

enum VariableTypes
{
	TYPE_CHAR,
	TYPE_FLOAT,
	TYPE_INT
};

enum CollisionObjects
{
	COLLISION_SPRITE,
	COLLISION_MAP,
	COLLISION_SCREEN,

	COLLISION_TYPES_COUNT
};

enum CollisionResults
{
	NO_COLLISION,
	COLLIDE_LEFT,
	COLLIDE_RIGHT,
	COLLIDE_DOWN,
	COLLIDE_UP, 
	COLLIDE_SPRITE,

	COLLIDE_COUNT
};

enum AttributeEffects
{
	ATTRIBUTE_BLOCK = COLLIDE_COUNT,
	ATTRIBUTE_DAMAGE,
	ATTRIBUTE_HEAL,
	ATTRIBUTE_REPEL,
	ATTRIBUTE_NONE,

	ATTRIBUTE_COUNT

};

enum Directoins
{
	NO_DIRECTION,
	DOWN_DIRECTION,
	LEFT_DIRECTION,
	RIGHT_DIRECTION,
	UP_DIRECTION,

	DIRECTION_COUNT
};

#endif // _UTIL_H_