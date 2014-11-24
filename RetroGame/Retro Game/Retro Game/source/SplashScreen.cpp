#include "SplashScreen.h"

#include "Sprites.h"
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

}

void SplashScreen::UpdateState( float a_fDelta )
{
	a_fDelta;
	DrawSprite( Sprites::GetInstance()->GetSprite( MENU_SPRITE ) );

	DrawString( "Spacebar to continue...", 100, 500 );

	for( int i = 0; i < KEY_LAST; ++i )
	{
		if( StateManager::GetInstance()->KeysList[i] == true )
		{
			switch( i )
			{
			case KEY_SPACE:
				StateManager::GetInstance()->EnterState( MENU_STATE );
				break;
			}
		}		
	}
}

void SplashScreen::LeaveState()
{

}