#include "MainMenu.h"

#include "Sprites.h"
#include "StateManager.h"

MainMenu::MainMenu() : State()
{

}

MainMenu::~MainMenu()
{

}

void MainMenu::InitState()
{

}

void MainMenu::UpdateState( float a_fDelta )
{
	a_fDelta;
	DrawSprite( Sprites::GetInstance()->GetSprite( MENU_SPRITE ) );

	DrawString( "Press 'N' to start a new game.", 100, 500 );
	DrawString( "Press 'H' to access high scores.", 100, 550 );
	DrawString( "Press 'C' to access credits.", 100, 600 );
	DrawString( "Press 'Q' to to quit the game.", 100, 650 );


	for( int i = 0; i < KEY_LAST; ++i )
	{
		if( StateManager::GetInstance()->KeysList[i] == true )
		{
			switch( i )
			{
			case 'N':
				StateManager::GetInstance()->EnterState( GAME_STATE );
				break;

			case 'H':				
				StateManager::GetInstance()->EnterState( HIGH_SCORES_STATE );
				break;

			case 'C':				
				StateManager::GetInstance()->EnterState( CREDITS_STATE );
				break;
				
			case 'Q':				
				StateManager::GetInstance()->EnterState( END_STATE );
				break;
			}
		}		
	}
}

void MainMenu::LeaveState()
{

}