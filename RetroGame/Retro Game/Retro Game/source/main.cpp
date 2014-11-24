// Entry point to program
#include "StateManager.h"

int main()
{	
	StateManager* pGame = StateManager::CreateInstance();
	pGame->Update();
	delete pGame;

	return 0;
}