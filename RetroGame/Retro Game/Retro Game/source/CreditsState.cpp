#include "CreditsState.h"

#include "Sprites.h"
#include "StateManager.h"

CreditsState::CreditsState() : State()
{

}

CreditsState::~CreditsState()
{

}

void CreditsState::InitState()
{

}

void CreditsState::UpdateState( float a_fDelta )
{
	a_fDelta;
	DrawSprite( Sprites::GetInstance()->GetSprite( MENU_SPRITE ) );
	
	DrawString( "Credits: ", 100, 200 ); 
	DrawString( "Art created by April Riley, Danny McNeill, Jordan Zaz, ", 120, 250 );
	DrawString( "Niel Williams and Ryley Swan", 120, 280 );

	DrawString( "AIE Framework written by Jamie Stewart.", 120, 350 );

	DrawString( "Other code written by Nick Smith.", 120, 400 );


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

void CreditsState::LeaveState()
{

}