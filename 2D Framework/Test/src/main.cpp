#include "StateManager.h"

int main()
{
	StateManager* pGame = StateManager::Create();
	pGame->Update();
	pGame->Destroy();

	return 0;
}