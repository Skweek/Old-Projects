#include "SplashScreen.h"

#include "StateManager.h"

SplashScreen::SplashScreen() : State()
{
	InitState();
}

SplashScreen::~SplashScreen()
{

}

void SplashScreen::InitState()
{
	SetLayout( 0 );
	ToggleLayoutDrawing( true );
	ToggleMapDrawing( false );
}

void SplashScreen::UpdateState( float a_fDelta, int* a_iKeys )
{

}

void SplashScreen::LeaveState()
{

}