////////////////////////////////////////////////////////////
// File: Enums.h
// Author: Nick Smith
// Date Created: 16th April 2013
// Brief: Collection of all enumerators
////////////////////////////////////////////////////////////

#ifndef _ENUMS_H_
#define _ENUMS_H_

/*	GAME_STATES			*/
enum GameStates
{
	NO_STATE,
	SPLASH_SCREEN_STATE,
	MENU_STATE,
	CREDITS_STATE,
	HIGH_SCORES_STATE,
	GAME_STATE,
	GAME_OVER_STATE,
	END_STATE
};

/*	Sprites				*/
enum SpriteID
{
	TILE_SHEET_SPRITE,
	GROUND_MAP_SPRITE,

	// UI Sprites
	MENU_SPRITE,

	// Player and stuff
	PLAYER_SPRITE,
	BULLET_SPRITE,
	BOMBER_JET_SRPITE,
	FIGHTER_JET_SPRITE,

	// IN GAME Sprites
	HEALTH_BG_SPRITE,
	PLAYER_LIVES_SPRITE,
	PLAYER_HEALTH_SPRITE,

	// Sprite count
	SPRITE_COUNT
};

/*	Tiles Enum			*/
enum Tiles
{
	NO_TILE,
	// Magma path tiles
	MAGMA_TOP_LEFT,
	MAGMA_TOP_RIGHT,
	MAGMA_TOP_MIDDLE,
	MAGMA_MIDDLE_LEFT,
	MAGMA_MIDDLE_RIGHT,
	MAGMA_MIDDLE_MIDDLE,
	MAGMA_BOTTOM_LEFT,
	MAGMA_BOTTOM_RIGHT,
	MAGMA_BOTTOM_MIDDLE,
	MAGMA_HOLE,
	MAGMA_DIAGONAL1,
	MAGMA_DIAGONAL2,
	EMPTY_TILE,

	// Tile count
	TILE_COUNT
};

/*	Enemy Type Enum		*/
enum EnemyTypes
{
	NONE,
	BOMBER_JET_ENEMY,
	FIGHTER_JET_ENEMY,
	BOSS_ENEMY,

	// count
	ENEMY_COUNT
};

/*	Menu Options		*/
enum MenuOptions
{
	NEW_GAME_OPTION,
	QUIT_OPTION,
	MENU_CREDITS_OPTION
};

/*	Tile enum			*/
enum TileTypes
{
	NORMAL_TILE,
	BLOCKED_TILE,
	ENEMY_TILE,
	ITEM_TILE
};

/*	Directions enum		*/
enum Key
{
	NO_KEY,
	RIGHT_DIR,
	LEFT_DIR,
	UP_DIR,
	DOWN_DIR
};

/*	Speed rating enum	*/
enum Speed
{
	STOPPED_SPEED,
	SLOWEST_SPEED,
	SLOW_SPEED,
	NORMAL_SPEED,
	FAST_SPEED,
	FASTEST_SPEED
};

/*	Collision effects	*/
enum CollisionEffects
{
	TAKE_DAMAGE_EFFECT,
	GIVE_HEALTH_EFFECT,
	STOP_MOVEMENT_EFFECT,

	// count
	EFFECT_COUNT
};

/*	Keyboard commands	*/
enum KeyCommands
{
	// Level Commands
	MOVE_PLAYER_UP,
	MOVE_PLAYER_DOWN,
	MOVE_PLAYER_LEFT,
	MOVE_PLAYER_RIGHT,
	SHOOT_PLAYER_BULLET,
	GOTO_PAUSE_MENU,

	// count
	COMMAND_COUNT
};

#endif