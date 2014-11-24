#include "StateManager.h"

#include "State.h"

//+===================================+//
//	Included states
	#include "SplashScreen.h"
	#include "MainMenu.h"
	#include "GameState.h"
	#include "MediaPlayer.h"
//+===================================+//

StateManager* StateManager::m_pStateManager = nullptr;

// If state doesn't exist create one and return it
StateManager* StateManager::Create()
{
	if( !m_pStateManager )
	{
		m_pStateManager = new StateManager;
	}

	return m_pStateManager;
}

// Deletes the current instance if it exists
void StateManager::Destroy()
{
	if( m_pStateManager )
	{
		delete m_pStateManager;
		m_pStateManager = nullptr;
	}
}

// Returns the current instance if it exists
StateManager* StateManager::Get()
{
	if( m_pStateManager )
	{		
		return m_pStateManager;
	}
	return nullptr; // Needs error handling

}

StateManager::StateManager()
{
	m_pPreviousState = 0;
	m_pCurrentState = 0;
	Init();
}

StateManager::~StateManager()
{
	FrameworkClose();
}

// Set up framework and load files needed throughout game
void StateManager::Init()
{
	InitialWindow = 0;
	m_ccWindowTitle = "";
	m_pWindowSize = Vec2( 500, 500 );

	// Initialise the framework
	StartFramework( (int)m_pWindowSize[0], (int)m_pWindowSize[1] );
	SetWindowTitle( InitialWindow, m_ccWindowTitle );

	LoadResources();
}

void StateManager::LoadResources()
{
	// Load layouts
	Layouts[0] = LoadLayout( "layouts/splashScreen.xml" ); // - Splashscreen
	Layouts[1] = LoadLayout( "layouts/mainMenu.xml" ); // - Main Menu
	Layouts[2] = LoadLayout( "layouts/gameState.xml" ); // - Game UI
	//Layouts[3] = LoadLayout( "layouts/layout1.xml" ); // - Credits
	//Layouts[4] = LoadLayout( "layouts/layout1.xml" ); // - High Scores
	//Layouts[5] = LoadLayout( "layouts/layout1.xml" ); // - End Game

	// Load Map Objects
	MapObjects = LoadObjects( "maps/objects.xml" );

	// Load Maps
	Maps[0] = LoadMap( "maps/map1.xml" );

	// Load Fonts
	Fonts[0] = LoadFont( "fonts/tnr.fnt" );

	// When linking UI elements make sure the correct layout is selected
	SetLayout( Layouts[0] ); // Splash screen
	SetLayout( Layouts[1] ); // Main Menu

	m_bRunning = true; // Game will shutdown as soon as this is false

	// Testing sounds
	int BGM = LoadBGMFile( "sounds/firebird.mp3" );
	int SFX = LoadSFXFile( "sounds/button.mp3" );
	SetCurrentBGM( BGM );
	SetCurrentSFX( SFX );

	// Set the current state to splash screen
	EnterState( SPLASH_SCREEN_STATE );
}

// Takes the next state name to enter as an
// int, stores the previous state in case we
// need to switch back to it or get information
// from it
void StateManager::EnterState( int a_iStateName )
{
	if ( a_iStateName != 0 )
	{
		if ( m_pPreviousState != 0 )
		{
			delete m_pPreviousState;
		}

		m_pPreviousState =  m_pCurrentState;

		switch( a_iStateName )
		{
		case SPLASH_SCREEN_STATE:
			m_pCurrentState = new SplashScreen();
			break;
		case MAIN_MENU_STATE:
			m_pCurrentState = new Menu();
			break;
		case GAME_STATE:
			m_pCurrentState = new GameState();
			break;
		case MEDIA_PLAYER:
			m_pCurrentState = new MediaPlayer();
			break;

		default:
			// No valid state entered so stay in current state
			break;
		}
	}
}

// Main loop that is determined by current state
// also gets an updated keylist for input
void StateManager::Update()
{
	int r = 0;
	do
	{		
		// Update our key list with current presses
		m_iKeyList = CheckInput();

		// Pressing ` key will reload map for debugging
		if( m_iKeyList[KEY_GRAVE_ACCENT] == 1 )
		{
			Maps[0] = LoadMap( "maps/map1.xml" );
		}
		// Pressing F5 will reload script file
		if( m_iKeyList[KEY_F5] == 1 )
		{
			ReloadScripts();

			// Load Maps
			Maps[0] = LoadMap( "maps/map1.xml" );
		}
		if( m_iKeyList['P'] == 1 )
		{
			//Pause();
		}

		char sp[256]; 
        sprintf_s( sp, "%f", GetFPS() ); 
		SetWindowTitle( InitialWindow, sp );
		
		r = rand() % 4;
		switch(r)
		{
		case 0:
			// Clear the screen
			RefreshScreen( InitialWindow, 0.5f, 0.f, 0.f, 0 );
			break;
		case 1:
			// Clear the screen
			RefreshScreen( InitialWindow, 0.f, 0.5f, 0.f, 0 );
			break;
		case 2:
			// Clear the screen
			RefreshScreen( InitialWindow, 0.f, 0.f, 0.5f, 0 );
			break;
		case 3:
			// Clear the screen
			RefreshScreen( InitialWindow, 0.2f, 0.2f, 0.2f, 0 );
			break;
		default:
			// Clear the screen
			RefreshScreen( InitialWindow, 0.5f, 0.5f, 0.5f, 0 );
			break;
		}


		// Call the current states update function
		m_pCurrentState->UpdateState( (float)GetDeltaTime(), m_iKeyList );
	}
	while ( m_bRunning && FrameworkUpdate() );
}

State* StateManager::GetCurrentState()
{
	return m_pCurrentState;
}

State* StateManager::GetPreviousState()
{
	return m_pPreviousState;
}

//+===================================+//
//	UI Element Functions
//+===================================+//
void StateManager::MainMenu()
{
	EnterState( MAIN_MENU_STATE );
}

void StateManager::NewGame()
{
	EnterState( GAME_STATE );
}

void StateManager::Quit()
{
	m_bRunning = false;
}