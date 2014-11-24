#include "MediaPlayer.h"

#include "StateManager.h"

MediaPlayer::MediaPlayer() : State()
{
	InitState();
}

MediaPlayer::~MediaPlayer()
{

}

void MediaPlayer::InitState()
{
	ToggleLayoutDrawing( false );
	ToggleMapDrawing( false );
	SetBGMPlaying( true );
	LineEnds = new Vec2[256];
	// Set the initial line pos
	for( int i = 0; i < 256; ++i )
	{
		LineEnds[i] = Vec2( i * 2.f, 0.f );
	}
}

void MediaPlayer::UpdateState( float a_fDelta, int* a_iKeys )
{
	spec = GetBGMSpectrum();

	DrawLine( Vec2(), Vec2( 500, 200 ), Vec4( 1, 1, 1, 1 ) );
	for( int i = 0; i < 256; ++i )
	{
		LineEnds[i].m_fY = 400 * spec[i];
	}
	for( int i = 0; i < 256; ++i )
	{
		DrawLine( Vec2( LineEnds[i].m_fX, 0.f ), LineEnds[i], Vec4( 1, 1, 1, 1 ) );
	}

	
}

void MediaPlayer::LeaveState()
{

}