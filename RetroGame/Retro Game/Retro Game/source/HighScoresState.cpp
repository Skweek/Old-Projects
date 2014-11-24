#include "HighScoresState.h"

#include "Sprites.h"
#include "StateManager.h"

HighScoresState::HighScoresState() : State()
{

}

HighScoresState::~HighScoresState()
{

}

void HighScoresState::InitState()
{

}

void HighScoresState::UpdateState( float a_fDelta )
{
	a_fDelta;
	DrawSprite( Sprites::GetInstance()->GetSprite( MENU_SPRITE ) );

	DrawString( "Highscores", 200, 300 );
	
	DrawString( "1st - 1000", 200, 350 );
	DrawString( "2nd - 800", 200, 380 );
	DrawString( "3rd - 500", 200, 410 );
	
	DrawString( "Press Enter to go back to menu.", 100, 550 );

	for( int i = 0; i < KEY_LAST; ++i )
	{
		if( StateManager::GetInstance()->KeysList[i] == true )
		{
			switch( i )
			{
			case KEY_ENTER:
				StateManager::GetInstance()->EnterState( MENU_STATE );
				break;
			}
		}		
	}
}

void HighScoresState::LeaveState()
{

}