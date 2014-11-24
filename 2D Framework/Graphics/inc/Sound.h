////////////////////////////////////////////////////////////
// File: Sound.h
// Author: Nick Smith
// Date Created: 23rd July 2013
// Brief: Sound handler
////////////////////////////////////////////////////////////
#ifndef _SOUND_H_
#define _SOUND_H_

#include "Utilities.h" 

// FMOD include file (C++)
#include "fmod.hpp"

/*	Initialises the sound library	*/
bool InitSound();

/*	Load sound files, returns the ID of the sound loaded	*/
int LoadBGM( const char* a_ccBGMFile );
int LoadSFX( const char* a_ccSFXFile );

/*	Update function, should be called once per
	frame update. Updates sounds and applies required effects	*/
void UpdateSounds();

/*	Sets the current sounds to be played.
	To-Do: Multiple sfx channels.	*/
void SetBGM( int a_iID );
void SetSFX( int a_iID );

/*	Simply plays/pauses music channels	*/
void PlayBGM();
void PlaySFX();
void PauseBGM();
	 
/*	Other stuff	*/
float* UpdateBGMSpectrum();
float* BGMSpectrum();

/*	Shuts down the sound library, cleans up any memory used.	*/
void ShutDownSound();

#endif // _SOUND_H_