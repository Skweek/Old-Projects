#include "GameOverState.h"

#include "Sprites.h"
#include "StateManager.h"

GameOverState::GameOverState() : State()
{
	// Score and success status is stored in state in
	// a vector 2 for access
	// Success is x, score is y
	m_bSuccess = (bool)StateManager::GetInstance()->GetPreviousState()->m_bLevelSuccess;
	m_iScore = (int)StateManager::GetInstance()->GetPreviousState()->m_iFinalScore;
}

GameOverState::~GameOverState()
{

}

void GameOverState::InitState()
{

}

void GameOverState::UpdateState( float a_fDelta )
{
	a_fDelta;
	DrawSprite( Sprites::GetInstance()->GetSprite( MENU_SPRITE ) );
	
	if ( m_bSuccess )
	{		
		DrawString( "Well done, you beat the game.", 100, 500 );
	}
	else
	{		
		DrawString( "Good stuff, you went and died...", 100, 500 );
	}
	char Buff[50];
	sprintf( Buff, "Your final score was: %i", m_iScore );
	DrawString( Buff, 100, 550 );
	DrawString( "Press Enter to go back to menu.", 100, 600 );


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

void GameOverState::LeaveState()
{

}