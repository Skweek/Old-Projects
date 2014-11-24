#include "MainMenu.h"

#include "StateManager.h"

Menu::Menu() : State()
{
	InitState();
}

Menu::~Menu()
{

}

void Menu::InitState()
{

}

void Menu::UpdateState( float a_fDelta, int* a_iKeys )
{
	SetLayout( 1 );
	ToggleLayoutDrawing( true );
	ToggleMapDrawing( false );
}

void Menu::LeaveState()
{

}