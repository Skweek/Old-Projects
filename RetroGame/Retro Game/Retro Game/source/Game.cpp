#include "AIE.h"
#include "Game.h"
#include "UI.h"
#include "Level.h"
#include "InputHandler.h"
#include "Vec2.h"
#include <time.h>
#include <iostream>
#include "Timer.h"

// Constructors and destructor
Game::Game()
{
	Initialise( m_iScreenWidth, m_iScreenHeight, false, "" );
	Init();
}

Game::Game( const char* a_cWindowTitle )
{
	Initialise( m_iScreenWidth, m_iScreenHeight, false, a_cWindowTitle );
	Init();
}

Game::~Game()
{
	delete Interfaces;
	delete Input;	
	delete LevelHandle;

	for ( int i = 0; i < SPRITE_COUNT; ++i )
	{
		DestroySprite( m_uiSpriteList[i] );
	}

	Shutdown();
}

void Game::Init()
{
	srand( (int)time(NULL) );
	m_bRunning = true;
	m_bGameInProgress = false;
	m_iGameState = MENU_STATE;
	m_iMenuState = SPLASHSCREEN_STATE;
	m_fGameTime = 0;
	m_fTimeSinceLastFrame = 0;

	LoadAssets();
	Interfaces = new UI( this );
	Input = new InputHandler;
	LevelHandle = new Level( this );
	EnemyWaves = new Timer;

}

void Game::LoadAssets()
{
	// Load menu screens
	m_uiSpriteList[MENU_SPRITE] = CreateSprite( "./images/UI/SplashScreen.png", m_iScreenWidth, m_iScreenHeight, false );

	// Load in Game UI	and set positions
	m_uiSpriteList[HEALTH_BG_SPRITE] = CreateSprite( "./images/UI/GenericUIBG.png", 600, 40, false );
	m_uiSpriteList[PLAYER_LIVES_SPRITE] = CreateSprite( "./images/HelicopterTop.png", 30, 30, true );
	m_uiSpriteList[PLAYER_HEALTH_SPRITE] = CreateSprite( "./images/UI/HealthOverlay.png", 200, 30, false );
	m_uiSpriteList[BOSS_HEALTH_SPRITE] = CreateSprite( "./images/UI/HealthOverlay.png", 500, 30, false );

	// Player sprites
	m_uiSpriteList[PLAYER_SPRITE] = CreateSprite( "./images/HelicopterTop.png", 64, 64, false );
	m_uiSpriteList[BULLET_SPRITE] = CreateSprite( "./images/crate_sideup.png", 5, 5, false );
	m_uiSpriteList[TURRET_SPRITE] = CreateSprite( "./images/tank_topdown.png", 32, 32, false );
	m_uiSpriteList[FIGHTER_JET_SPRITE] = CreateSprite( "./images/HelicopterTop.png", 32, 32, false );
	m_uiSpriteList[BOSS_SPRITE] = CreateSprite( "./images/tank_topdown.png", 100, 100, false );

	// Load the tile sheet
	m_uiSpriteList[TILE_SHEET_SPRITE] = CreateSprite( "./images/Tiles/TileSheet.png", 32, 32, false );
	m_uiSpriteList[GROUND_MAP_SPRITE] = CreateSprite( "./images/Tiles/Lava.png", m_iScreenWidth, m_iScreenHeight, false );

}

void Game::Loop()
{
	do
	{
		m_fTimeSinceLastFrame = GetDeltaTime();
		m_fGameTime += m_fTimeSinceLastFrame;

		Input->Update( this );
		KeyList = Input->GetKeyList();

		ClearScreen();

		switch ( m_iGameState )
		{
		case MENU_STATE:
			Interfaces->Update();
			MenuKeyActions();
			break;

		case GAME_STATE:
			EnemyWaves->Update();
			LevelHandle->Update();
			InGameKeyActions();
			break;

		case END_STATE:
			m_bRunning = false;
			break;

		default:
			m_iGameState = END_STATE;
			break;
		}

	} 
	while ( m_bRunning && FrameworkUpdate() == false );
}



#pragma region Get/Set Game Variables

int Game::GetGameState()
{
	return m_iGameState;
}

int Game::GetMenuState()
{
	return m_iMenuState;
}

void Game::SetGameState( int a_iGameState )
{
	m_iGameState = a_iGameState;
}

void Game::SetMenuState( int a_iMenuState )
{
	m_iMenuState = a_iMenuState;
}

unsigned int Game::GetSprite( int a_iSprite )
{
	return m_uiSpriteList[a_iSprite];
}

float Game::GetGameTime()
{
	return m_fGameTime;
}

float Game::GetTimeSinceLastFrame()
{
	return m_fTimeSinceLastFrame;
}

int Game::GetWindowHeight()
{
	return m_iScreenHeight;
}

int Game::GetWindowWidth()
{
	return m_iScreenWidth;
}

int Game::GetMapHeight()
{
	return m_iMapHeight;
}

int Game::GetMapWidth()
{
	return m_iMapWidth;
}

int* Game::GetKeys()
{
	return KeyList;
}
#pragma endregion

void Game::MenuKeyActions()
{
	for ( int i = 0; i < KEY_LAST; ++i )
	{
		if ( KeyList[i] == 1 )
		{
			switch( i )
			{
			case KEY_SPACE:
				m_iMenuState = MAINMENU_STATE;
				break;
			case 'N':
				m_iMenuState = NULL;
				m_iGameState = GAME_STATE;
				EnemyWaves->Start( 5.f );
				break;
			case 'Q':
				m_iGameState = END_STATE;
				break;
			case 'H':
				m_iMenuState = HIGHSCORES_STATE;
				break;
			case KEY_ESC:
				if ( m_iMenuState == PAUSEMENU_STATE )
				{
					m_iMenuState = MAINMENU_STATE;
				}
				break;
			}
		}
	}
}

void Game::InGameKeyActions()
{
	for ( int i = 0; i < KEY_LAST; ++i )
	{
		if ( KeyList[i] == 1 )
		{
			switch( i )
			{
			case KEY_ESC:
				m_iGameState = MENU_STATE;
				m_iMenuState = PAUSEMENU_STATE;
				break;
			default:
				break;
			}
		}
	}
}
