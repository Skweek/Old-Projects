#include "Sound.h"

FMOD_RESULT errorcheck;
FMOD::System* soundSystem;
FMOD::Sound* currentSFX;
FMOD::Sound* currentBGM;
FMOD::Channel* SFXChannel;
FMOD::Channel* BGMChannel;

std::map<int, FMOD::Sound*> BGMList;
std::map<int, FMOD::Sound*> SFXList;

float* fBGMSpectrum = new float[256];

int iNumBGM, iNumSFX;
bool InitSound()
{
	// Create sound system
	errorcheck = FMOD::System_Create( &soundSystem );
	if( errorcheck  != FMOD_OK )
	{
		printf( "FMOD error! (%d)\n", errorcheck );
		return false;
	}

	errorcheck = soundSystem->init( 100, FMOD_INIT_NORMAL, 0 );
	if( errorcheck  != FMOD_OK )
	{
		printf( "FMOD error! (%d)\n", errorcheck );
		return false;
	}

	iNumBGM = 0;
	iNumSFX = 0;
	
	printf( "%f", sizeof(FMOD::Channel) );

	return true;
}

void ShutdownSound()
{
	soundSystem->close();
	// To-Do: Clean up sound/channel maps
}

int LoadBGM( const char* a_ccBGMFile )
{
	if( a_ccBGMFile != NULL )
	{
		FMOD::Sound* tempSound;
		errorcheck = soundSystem->createStream( a_ccBGMFile, FMOD_DEFAULT | FMOD_SOFTWARE, 0, &tempSound );
		if( errorcheck  != FMOD_OK )
		{
			printf( "FMOD error! (%d)\n", errorcheck );
			return false;
		}
		// Put the sound file into the appropriate map
		BGMList.insert( std::pair<int, FMOD::Sound*>( iNumBGM, tempSound ) );
		++iNumBGM;

		return iNumBGM - 1;
	}

	return NULL;
}

int LoadSFX( const char* a_ccSFXFile )
{
	if( a_ccSFXFile != NULL )
	{
		FMOD::Sound* tempSound;
		errorcheck = soundSystem->createSound( a_ccSFXFile, FMOD_DEFAULT, 0, &tempSound );
		if( errorcheck  != FMOD_OK )
		{
			printf( "FMOD error! (%d)\n", errorcheck );
			return NULL;
		}
		// Put the sound file into the appropriate map
		SFXList.insert( std::pair<int, FMOD::Sound*>( iNumSFX, tempSound ) );
		++iNumSFX;

		return iNumSFX - 1;
	}
	
	return NULL;
}

void UpdateSounds()
{
	// To-Do:	Effects and stuff need to be added here
	//			I need to actually add in effects first though
	soundSystem->update();
	BGMChannel->setVolume( 0 );
	fBGMSpectrum = UpdateBGMSpectrum();
}

// Set the current BGM/SFX
void SetBGM( int a_iID )
{
	std::map<int, FMOD::Sound*>::iterator pIter;
	pIter = BGMList.find( a_iID );
	FMOD::Sound* temp = (*pIter ).second;
	currentBGM = temp;
	soundSystem->playSound( FMOD_CHANNEL_FREE, currentBGM, true, &BGMChannel );
}

void SetSFX( int a_iID )
{
	std::map<int, FMOD::Sound*>::iterator pIter;
	pIter = SFXList.find( a_iID );
	FMOD::Sound* temp = (*pIter ).second;
	currentSFX = temp;
	soundSystem->playSound( FMOD_CHANNEL_FREE, currentSFX, true, &SFXChannel );
}

// Play/Pause sounds
void PlayBGM()
{
	BGMChannel->setPaused( false );
}

void PauseBGM()
{
	BGMChannel->setPaused( true );
}

void PlaySFX()
{
	bool playing;
	SFXChannel->isPlaying(&playing);
	if( !playing )
	{
		SFXChannel->stop();
		soundSystem->playSound( FMOD_CHANNEL_FREE, currentSFX, true, &SFXChannel );
	}
	SFXChannel->setPaused( false );
}

float* UpdateBGMSpectrum()
{
	int iSampleSize = 256;
	float* fSpecLeft = new float[iSampleSize];
	float* fSpecRight = new float[iSampleSize];
	float* fSpectrum = new float[iSampleSize];

	// Get the spectrum
	BGMChannel->getSpectrum( fSpecLeft, iSampleSize, 0, FMOD_DSP_FFT_WINDOW_RECT );
	BGMChannel->getSpectrum( fSpecRight, iSampleSize, 1, FMOD_DSP_FFT_WINDOW_RECT );

	// Get average of left and right channel
	for( int i = 0; i < iSampleSize; ++i )
	{
		fSpectrum[i] = ( ( fSpecLeft[i] + fSpecRight[i] ) / 2 );
	}

	// Find max volume
	auto maxIterator = std::max_element(&fSpectrum[0], &fSpectrum[iSampleSize]);
	float maxVol = *maxIterator;
 
	// Normalize
	if (maxVol != 0)
		std::transform(&fSpectrum[0], &fSpectrum[iSampleSize], &fSpectrum[0], [maxVol] (float dB) -> float { return dB / maxVol; });
	
	delete fSpecLeft;
	delete fSpecRight;
	return fSpectrum;
}

float* BGMSpectrum()
{
	return fBGMSpectrum;
}