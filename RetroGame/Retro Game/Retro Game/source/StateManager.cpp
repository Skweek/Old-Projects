#include "StateManager.h"
#include "InputHandler.h"
#include "Sprites.h"

//+===================================+//
//	Included states
#include "GameState.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "GameOverState.h"
#include "CreditsState.h"
#include "HighScoresState.h"
//+===================================+//

const int m_iScreenHeight = 800;
const int m_iScreenWidth = 640;
	 
const int m_iMapHeight = 200;
const int m_iMapWidth = m_iScreenWidth/32;

StateManager* StateManager::m_pStateManager = nullptr;

// If state doesn't exist create one and return it
StateManager* StateManager::CreateInstance()
{
	if( !m_pStateManager )
	{
		m_pStateManager = new StateManager;
	}

	return m_pStateManager;
}

// Deletes the current instance if it exists
void StateManager::DestroyInstance()
{
	if( m_pStateManager )
	{
		delete m_pStateManager;
		m_pStateManager = nullptr;
	}
}

// Returns the current instance if it exists
StateManager* StateManager::GetInstance()
{
	if( m_pStateManager )
	{		
		return m_pStateManager;
	}
	return nullptr; // Needs error handling

}

StateManager::StateManager()
{
	Init();
}

StateManager::~StateManager()
{
	Shutdown();
}

// Set up framework and Create initial instances of 
// Sprites and Input, sets current state to the 
// splash screen
void StateManager::Init()
{
	Initialise( m_iScreenWidth, m_iScreenHeight, false, "" );
	m_pCurrentState = new SplashScreen();
	m_pPreviousState = new SplashScreen();
	InputHandler::CreateInstance();
	Sprites::CreateInstance();
}

// Takes the next state name to enter as an
// int, stores the previous state in case we
// need to switch back to it or get information
// from it
void StateManager::EnterState( int a_iStateName )
{
	if ( a_iStateName )
	{
		if ( m_pPreviousState )
		{
			delete m_pPreviousState;
		}

		m_pPreviousState =  m_pCurrentState;

		switch( a_iStateName )
		{
		case SPLASH_SCREEN_STATE:
			m_pCurrentState = new SplashScreen();
			break;
		case MENU_STATE:
			m_pCurrentState = new MainMenu();
			break;
		case HIGH_SCORES_STATE:
			m_pCurrentState = new HighScoresState();
			break;
		case CREDITS_STATE:
			m_pCurrentState = new CreditsState();
			break;
		case GAME_OVER_STATE:
			m_pCurrentState = new GameOverState();
			break;
		case GAME_STATE:
			m_pCurrentState = new GameState();
			break;
		case END_STATE:
			m_bRunning = false;
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
	do
	{
		ClearScreen();

		m_fTimeSinceLastFrame = GetDeltaTime();
		m_fGameTime += m_fTimeSinceLastFrame;
	
		InputHandler::GetInstance()->Update( m_fTimeSinceLastFrame );
		KeysList = InputHandler::GetInstance()->GetKeyList();
		m_pPreviousState;
		m_pCurrentState->UpdateState( m_fTimeSinceLastFrame );
	}
	while ( m_bRunning && FrameworkUpdate() == false );
}

Vec2 StateManager::GetWindowSize()
{
	return Vec2( (float)m_iScreenWidth, (float)m_iScreenHeight );
}

Vec2 StateManager::GetMapSize()
{
	return Vec2( (float)m_iMapWidth, (float)m_iMapHeight );
}

State* StateManager::GetCurrentState()
{
	return m_pCurrentState;
}

State* StateManager::GetPreviousState()
{
	return m_pPreviousState;
}