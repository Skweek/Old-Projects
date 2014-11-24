#include "GameState.h"
#include "Level.h"
#include "Enums.h"
#include "Sprites.h"
#include "StateManager.h"

GameState::GameState() : State()
{
	InitState();
}

GameState::~GameState()
{
	if ( LevelHandle )
	{
		delete LevelHandle;
	}
}

void GameState::InitState()
{
	LevelHandle = new Level();
	m_bPaused = false;
}

void GameState::UpdateState( float a_fDelta )
{
	LevelHandle->DrawLevel();
	if ( !m_bPaused )
	{
		LevelHandle->Update( a_fDelta );
	}
	DrawHUD();
}

void GameState::LeaveState()
{

}

void GameState::DrawHUD()
{
	DrawSprite( Sprites::GetInstance()->GetSprite( HEALTH_BG_SPRITE ) );

	float x = (LevelHandle->GetPlayerInfo().m_fX * 2.f );
	float y = 30.f;
	SetSpriteScale(  Sprites::GetInstance()->GetSprite( PLAYER_HEALTH_SPRITE ), x, y );
	DrawSprite( Sprites::GetInstance()->GetSprite( PLAYER_HEALTH_SPRITE ) );

	DrawString( "Lives: ", 15, m_iScreenHeight - 50 );
	for( int i = 0; i < LevelHandle->GetPlayerInfo().m_fY; ++i )
	{
		MoveSprite( Sprites::GetInstance()->GetSprite( PLAYER_LIVES_SPRITE ), i * 32.f + 80.f , (float)m_iScreenHeight - 50 );
		DrawSprite( Sprites::GetInstance()->GetSprite( PLAYER_LIVES_SPRITE ) );
	}

	char ScoreBuff[50];
	sprintf( ScoreBuff, "%i", LevelHandle->GetScore() );
	DrawString( ScoreBuff, m_iScreenWidth - 100, 10 );

	if ( LevelHandle->GetPlayerInfo().m_fY < 0 )
	{
		StateManager::GetInstance()->GetCurrentState()->m_bLevelSuccess = false;
		StateManager::GetInstance()->GetCurrentState()->m_iFinalScore = LevelHandle->GetScore();
		StateManager::GetInstance()->EnterState( GAME_OVER_STATE );
	}

	for( int i = 0; i < KEY_LAST; ++i )
	{
		if( StateManager::GetInstance()->KeysList[i] == true )
		{
			switch( i )
			{
			case KEY_ESC:
				if ( !m_bPaused )
				{
					m_bPaused = true;
				}
				break;
			}
		}		
	}

	if ( m_bPaused )
	{
		PauseMenu();
	}
}

void GameState::PauseMenu()
{
	DrawSprite( Sprites::GetInstance()->GetSprite( MENU_SPRITE ) );
	
	DrawString( "Press 'R' to resume game.", 100, 550 );
	DrawString( "Press 'M' to go to main menu.", 100, 600 );
	DrawString( "Press 'Q' to to quit the game.", 100, 650 );

	for( int i = 0; i < KEY_LAST; ++i )
	{
		if( StateManager::GetInstance()->KeysList[i] == true )
		{
			switch( i )
			{
			case 'R':
				m_bPaused = false;
				break;
			case 'M':
				StateManager::GetInstance()->EnterState( MENU_STATE );
				break;
			case 'Q':
				StateManager::GetInstance()->EnterState( END_STATE );
				break;
			}

		}		
	}
}