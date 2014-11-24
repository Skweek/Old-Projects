////////////////////////////////////////////////////////////
// File: Game.h
// Author: Nick Smith
// Date Created: 16th April 2013
// Brief: Main game initialisation/destrucion and update loop
////////////////////////////////////////////////////////////
#include "Enums.h"

#pragma warning (disable : 4996)

#ifndef _GAME_H_
#define _GAME_H_

class UI;
class InputHandler;
class Level;

struct Timer; // All timers in the actual game loop but public

const int m_iScreenHeight = 800;
const int m_iScreenWidth = 640;
	
const int m_iMapHeight = 200;
const int m_iMapWidth = m_iScreenWidth/32;

class Game
{
public:
	Game();
	Game( const char* a_cWindowTitle );
	~Game();
		
	void Loop();

	void MenuKeyActions();
	void InGameKeyActions();
	int* GetKeys();

	int GetGameState();
	int GetMenuState();
	void SetGameState( int a_iGameState );
	void SetMenuState( int a_iMenuState );
	int GetWindowHeight();
	int GetWindowWidth();
	int GetMapHeight();
	int GetMapWidth();

	unsigned int GetSprite( int a_iSprite );

	float GetGameTime();
	float GetTimeSinceLastFrame();

	Timer* EnemyWaves;

private:
	void Init();
	void LoadAssets();
	void CreateNewLevel();
	void DestroyLevel();
	void UpdateGameScreen();
	void CreateEnemies();
	void DeleteEnemy();

	bool m_bRunning;
	bool m_bGameInProgress;
	float m_fGameTime;
	float m_fTimeSinceLastFrame;

	int* KeyList;

	int m_iGameState;
	int m_iMenuState;

	unsigned int m_uiSpriteList[SPRITE_COUNT];

	UI* Interfaces;
	InputHandler* Input;
	Level* LevelHandle;

};

#endif