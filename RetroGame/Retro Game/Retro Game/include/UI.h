////////////////////////////////////////////////////////////
// File: UI.h
// Author: Nick Smith
// Date Created: 16th April 2013
// Brief: UI class
////////////////////////////////////////////////////////////

#ifndef _UI_H_
#define _UI_H_

class Game;

class UI
{
public:
	UI( Game* GameHandle );


	// Functions to display in game UI
	void PlayerHealth( int a_iHealth, int a_iLives );
	void BossHealth( int a_iHealth );

	void Update();
	void Draw();

	int m_iGameState;

private:
	unsigned int m_uiUI;
	Game* m_pGameHandle;

};

#endif