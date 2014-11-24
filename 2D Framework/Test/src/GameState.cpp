#include "GameState.h"

#include "StateManager.h"
#include "Player.h"

GameState::GameState() : State()
{
	InitState();
}

GameState::~GameState()
{
	delete m_pPlayer;
}

void GameState::InitState()
{
	SetLayout( 2 );
	SetMap( 0 );
	ToggleLayoutDrawing( true );
	ToggleMapDrawing( true );
	
	m_pPlayer = new Player( "actors/actor1/actor1.xml", Vec2( 20, 40 ), Vec2( 150, 100 ) );

	// This is the player we control with the keyboard
	m_pPlayer->SetKeys( KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT );

	SetBGMPlaying( true );
}

void GameState::UpdateState( float a_fDelta, int* a_iKeys )
{
	if( a_iKeys[KEY_ENTER] == 1 )
	{
		SetSFXPlaying();
	}

	m_pPlayer->Update( a_fDelta, a_iKeys );
	
	m_pPlayer->Draw();
}

void GameState::LeaveState()
{

}