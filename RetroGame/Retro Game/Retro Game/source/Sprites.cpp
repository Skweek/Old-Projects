#include "Sprites.h"

Sprites* Sprites::m_pSpriteList = nullptr;

// If state doesn't exist create one and return it
Sprites* Sprites::CreateInstance()
{
	if( !m_pSpriteList )
	{
		m_pSpriteList = new Sprites;
	}

	return m_pSpriteList;
}

// Deletes the current instance if it exists
void Sprites::DestroyInstance()
{
	if( m_pSpriteList )
	{
		delete m_pSpriteList;
		m_pSpriteList = nullptr;
	}
}

// Returns the current instance if it exists
Sprites* Sprites::GetInstance()
{
	if ( m_pSpriteList )
	{
		return m_pSpriteList;
	}
	return nullptr; // Needs error handling

}

Sprites::Sprites()
{
	LoadSprites();
}

void Sprites::LoadSprites()
{

	// Load menu screens
	SpritesList[MENU_SPRITE] = CreateSprite( "./images/UI/SplashScreen.png", m_iScreenWidth, m_iScreenHeight, false );

	// Load in Game UI	and set positions
	SpritesList[HEALTH_BG_SPRITE] = CreateSprite( "./images/UI/GenericUIBG.png", 220, 80, false );
	SpritesList[PLAYER_LIVES_SPRITE] = CreateSprite( "./images/HelicopterTop.png", 30, 30, false );
	SpritesList[PLAYER_HEALTH_SPRITE] = CreateSprite( "./images/UI/HealthOverlay.png", 180, 30, false );

	// Player sprites
	SpritesList[PLAYER_SPRITE] = CreateSprite( "./images/HelicopterTop.png", 64, 64, false );
	SpritesList[BULLET_SPRITE] = CreateSprite( "./images/bullet.png", 8, 8, false );
	SpritesList[BOMBER_JET_SRPITE] = CreateSprite( "./images/Bomber Jet.png", 32, 64, false );
	SpritesList[FIGHTER_JET_SPRITE] = CreateSprite( "./images/FighterJet.png", 32, 64, false );

	// Load the tile sheet
	SpritesList[TILE_SHEET_SPRITE] = CreateSprite( "./images/Tiles/TileSheet.png", 32, 32, false );
	SpritesList[GROUND_MAP_SPRITE] = CreateSprite( "./images/Tiles/Lava.png", m_iScreenWidth, m_iScreenHeight, false );


	// For sprites that don't move, set
	// Their positions now so it isn't 
	// called unnecessarily 
	MoveSprite( SpritesList[MENU_SPRITE], 0, 0 );
	MoveSprite( SpritesList[HEALTH_BG_SPRITE], 10, (float)m_iScreenHeight - 90 );
	MoveSprite( SpritesList[PLAYER_HEALTH_SPRITE], 20, (float)m_iScreenHeight - 80 );

}

// Returns the required sprite
unsigned int Sprites::GetSprite( int a_iSpriteID )
{
	return SpritesList[a_iSpriteID];
}