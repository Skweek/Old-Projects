////////////////////////////////////////////////////////////
// File: Enum.h
// Author: Nick Smith
// Date Created: 5th May 2013
// Brief: Enumerators
////////////////////////////////////////////////////////////
#ifndef _ENUM_H_
#define _ENUM_H_

enum Errors
{
	NO_ERROR_,
	LIBRARIES_FAILED_TO_LOAD,
	WINDOW_CREATION_FAILED,
	SHADER_DIDNT_COMPILE,
	PROGRAM_DIDNT_LINK,
	TEXTURE_FAILED_TO_LOAD,

	// error count
	ERROR_COUNT
};


#endif // _ENUM_H_