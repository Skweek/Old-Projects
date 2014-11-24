#include "InputHandler.h"
#include "Enums.h"

InputHandler* InputHandler::m_pInputHandler = nullptr;

// If state doesn't exist create one and return it
InputHandler* InputHandler::CreateInstance()
{
	if( !m_pInputHandler )
	{
		m_pInputHandler = new InputHandler();
	}

	return m_pInputHandler;
}

// Deletes the current instance if it exists
void InputHandler::DestroyInstance()
{
	if( m_pInputHandler )
	{
		delete m_pInputHandler;
		m_pInputHandler = nullptr;
	}
}

// Returns the current instance if it exists
InputHandler* InputHandler::GetInstance()
{
	if ( m_pInputHandler )
	{
		return m_pInputHandler;
	}
	return nullptr; // Needs error handling
}

InputHandler::InputHandler()
{
	KeyList = new Keys[ KEY_LAST ];
	m_fLastKeyPressTime = 0.0f;
}

InputHandler::~InputHandler()
{
	delete KeyList;
}

void InputHandler::Update( float a_fDelta )
{
	// Update all the key states
	for ( int i = 0; i < KEY_LAST; ++i )
	{
		if ( IsKeyDown( i ) )
		{
			KeyList[ i ].m_bPressed = true;
		} 
		else if ( !IsKeyDown( i ) ) 
		{			
			if ( KeyList[ i ].m_bPressed == true )
			{
				KeyList[ i ].m_bPressed = false;
				KeyList[ i ].m_bKeyUp = true;
			}
		}
	}
	if ( a_fDelta > ( m_fLastKeyPressTime + 0.005f ) )
	{
 		m_fLastKeyPressTime = a_fDelta;
	}
}

// Returns the a bool array for key presses
bool* InputHandler::GetKeyList()
{
	bool *TempList = new bool[KEY_LAST];
	for ( int i = 0; i < KEY_LAST; ++i )
	{
		TempList[i] = KeyList[i].m_bPressed;
	}

	return TempList;
}