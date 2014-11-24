#include "Level.h"
#include "Tile.h"
#include "Timer.h"
#include "AIE.h"
#include "Enums.h"
#include "Player.h"
#include "Bullet.h"
#include "EnemyManager.h"
#include "Collision.h"
#include <iostream>
#include "StateManager.h"
#include "Sprites.h"

Level::Level()
{
	m_iWaveInterval = 3;
	m_iNumberOfEnemiesToSpawn = 10;
	m_iRatioOfEnemyTypes = 5;

	m_iScore = 0;

	EnemyWaves = new Timer;

	EnemiesManager = new EnemyManager();	// makes sure enemylist is clear
	CreateLevel();
}

Level::~Level()
{
	DeleteLevel();
	delete Player1;
	delete EnemyWaves;
}

void Level::CreateLevel()
{
	// Set which rows are used to start rendering
	m_iCurTopRow = m_iMapHeight - ( m_iScreenHeight / 32 );
	m_iCurBotRow = m_iCurTopRow + ( m_iScreenHeight / 32 );

	// Create Array
	MapGrid = new Tile*[m_iMapWidth];
	for ( int i = 0; i < m_iMapWidth; ++i )
	{
		MapGrid[i] = new Tile[m_iMapHeight];
	}

	// First set the 2 columns on the side to be borders
	// and the 2 columns to the side of those to empty 
	for ( int Y = 0; Y < m_iMapHeight; ++Y )
	{
		for ( int X = 0; X < m_iMapWidth; ++X )
		{
			// Set the initial positions of all the tiles
			MapGrid[X][Y].m_pTilePos = Vec2( X * 32.f, (float)m_iScreenHeight - ( ( m_iMapHeight * 32 ) - ( Y * 32 ) ) );
		}

		MapGrid[0][Y].m_iTileID = MAGMA_MIDDLE_RIGHT;
		MapGrid[1][Y].m_iTileID = NO_TILE;
		MapGrid[2][Y].m_iTileID = MAGMA_MIDDLE_LEFT;
		MapGrid[m_iMapWidth - 1][Y].m_iTileID = MAGMA_MIDDLE_LEFT;
		MapGrid[m_iMapWidth - 2][Y].m_iTileID = NO_TILE;
		MapGrid[m_iMapWidth - 3][Y].m_iTileID = MAGMA_MIDDLE_RIGHT;

		// The rest of the tiles will be randomly generated to be lava tiles
		for ( int X = 3; X < m_iMapWidth - 3; ++X )
		{
			int randomnumber = rand() % 10;
			if ( randomnumber == 1 )
			{
				MapGrid[X][Y].m_iTileID = MAGMA_HOLE;
				MapGrid[X][Y].m_iTileType = BLOCKED_TILE;
			}
			else
			{
				MapGrid[X][Y].m_iTileID = MAGMA_MIDDLE_MIDDLE;
				MapGrid[X][Y].m_iTileType =  NORMAL_TILE;
			}
		}
	}
	
	// Create Player	
	Player1 = new Player( Vec2( (float)m_iScreenWidth / 2.f, (float)m_iScreenHeight - 50.f ), Vec2( 64.f, 64.f ), NORMAL_SPEED, Sprites::GetInstance()->GetSprite(PLAYER_SPRITE), 100.f );

	// Start timer
	EnemyWaves->Start( (float)m_iWaveInterval );
}

void Level::DeleteLevel()
{
	for ( int i = 0; i < m_iMapWidth; ++i )
	{
		if ( MapGrid[i] != nullptr )
		{
			delete MapGrid[i];
		}
	}
	delete MapGrid;
}

void Level::DrawLevel()
{	
	// Move ground sprite to 0,0
	MoveSprite(  Sprites::GetInstance()->GetSprite(GROUND_MAP_SPRITE), Vec2( 0.f, 0.f ) );
	DrawSprite(  Sprites::GetInstance()->GetSprite(GROUND_MAP_SPRITE) );

	for ( int Y = m_iCurTopRow - 2; Y < m_iCurBotRow; ++Y )
	{
		for ( int X = 0; X < m_iMapWidth; ++X )
		{
			SetSpriteUVCoordinates( Sprites::GetInstance()->GetSprite( TILE_SHEET_SPRITE ), MapGrid[X][Y].m_iTileID / float( TILE_COUNT ), 0.f, ( MapGrid[X][Y].m_iTileID + 1.f ) / float( TILE_COUNT ), 1.f );
			MoveSprite( Sprites::GetInstance()->GetSprite( TILE_SHEET_SPRITE ), MapGrid[X][Y].m_pTilePos );
			DrawSprite( Sprites::GetInstance()->GetSprite( TILE_SHEET_SPRITE ) );
		}
	}	

	
	Player1->Draw();
}

void Level::MoveLevel()
{
	if ( m_iCurTopRow > 2 )
	{	
		for ( int X = 0; X < m_iMapWidth; ++X )
		{
			for ( int Y = 0; Y < m_iMapHeight; ++Y )
			{
				MapGrid[X][Y].m_pTilePos += Vec2 ( 0.f, 1.f );
			}
		}
	}

	// If the bottom row is outside of the screen then
	// Move the rendering up one
	if ( MapGrid[0][m_iCurBotRow-1].m_pTilePos.m_fY > m_iScreenHeight ) 
	{
		--m_iCurTopRow;
		--m_iCurBotRow;
	}
}

void Level::Update( float a_fDelta )
{
	ClearScreen();

	MoveLevel();

	EnemyWaves->Update();

	// Update and draw Player
	Player1->Update( a_fDelta, this, StateManager::GetInstance()->KeysList );

	// Update and draw Enemies
	if( EnemyWaves->m_bTimerFinished == true )
	{
		NewEnemyWave();
	}
	EnemiesManager->Update( a_fDelta, this );

	// Update and draw Bullets
	for ( int i = 0; i  < (int)Bullets.size() - 1; ++i ) 
	{
		Bullet* pBull = Bullets[i];
 		pBull->Update( a_fDelta );
	}
	
	// Collision Detection
	PlayerOutOfBounds();
	EnemyOutOfBounds();
	BulletOutOfBounds();
	BulletCollisions();
}

void Level::PlayerOutOfBounds()
{
	int iDir = 0;
	iDir = (Collision::CheckWallCollision( Player1->GetPos(), Vec2( (float)m_iScreenWidth, (float)m_iScreenHeight ) ) ) ;
	Player1->OnCollision( STOP_MOVEMENT_EFFECT, iDir );
}

void Level::EnemyOutOfBounds()
{
	for ( int i = 0; i < (int)EnemiesManager->EnemyList.size(); ++i )
	{
		if ( EnemiesManager->GetEnemyPosition( EnemiesManager->EnemyList[i] ).m_fY > m_iScreenHeight )
		{
			EnemiesManager->DeleteEnemy( EnemiesManager->EnemyList[i] );
		}
	}
}

void Level::BulletOutOfBounds()
{
	if ( Bullets.size() > 0 )
	{
		std::vector<Bullet*>::reverse_iterator pIter = Bullets.rbegin();
		for( ; pIter < Bullets.rend(); ++pIter )
		{
			Bullet* pBull = (*pIter);	
			if ( ( Collision::CheckWallCollision( pBull->GetPos(), Vec2( (float)m_iScreenWidth + pBull->GetSize().m_fX, (float)m_iScreenHeight ) ) ) != 0 )
			{
				DeleteBullet( pBull );
				break;
			}
		}
	}
}

void Level::DeleteBullet( Bullet* a_pBullet )
{
	std::vector<Bullet*>::reverse_iterator pIter = Bullets.rbegin();
	for( ; pIter < Bullets.rend(); ++pIter )
	{
		Bullet* pBull = (*pIter);	
		if ( pBull == a_pBullet )
		{
			delete pBull;
			Bullets.erase( --(pIter.base()) );
			break;
		}
	}
}

void Level::BulletCollisions()
{	
	for( int i = 0; i < (int)Bullets.size(); ++i )
	{
		Bullet* pBull = Bullets[i];	

		if ( pBull->GetDirection() == UP_DIR )
		{
			if( EnemiesManager->CheckCollision( pBull->GetPos(), pBull->GetSize(), pBull->GetDamage() ) )
			{
				m_iScore += pBull->GetDamage();
				DeleteBullet( pBull );
				break;
			}
		}
		else if ( pBull->GetDirection() == DOWN_DIR )
		{
			if( Collision::CheckBoxCollision( Player1->GetPos(), Player1->GetSize(), pBull->GetPos(), pBull->GetSize() ) )
			{
				Player1->OnCollision( TAKE_DAMAGE_EFFECT, pBull->GetDamage() );
				DeleteBullet( pBull );
				break;
			}
		}
	}
}

void Level::ShootBullet( Vec2 a_pPosition, int a_iDamage, int a_iDir )
{
 	Bullet* pBul = new Bullet( a_pPosition, a_iDamage, a_iDir, Sprites::GetInstance()->GetSprite(BULLET_SPRITE) );
	Bullets.push_back( pBul );
}

void Level::NewEnemyWave()
{
	EnemyWaves->Reset();

	int iNumberOfJets = m_iNumberOfEnemiesToSpawn / m_iRatioOfEnemyTypes;
	int iNumberOfBombers = m_iNumberOfEnemiesToSpawn - iNumberOfJets;

	int i;
	for ( i = 0; i < iNumberOfJets; ++i )
	{
		EnemiesManager->CreateEnemy( FIGHTER_JET_ENEMY, Vec2( ( rand() % 17 + 2 ) * 32.f, -64.f ), Vec2( 32.f, 32.f ), SLOW_SPEED, Sprites::GetInstance()->GetSprite(FIGHTER_JET_SPRITE), 20.f );
	}

	for ( i = 0; i < iNumberOfBombers; ++i )
	{
		EnemiesManager->CreateEnemy( BOMBER_JET_ENEMY, Vec2( ( rand() % 17 + 2 ) * 32.f, -32.f ), Vec2( 32.f, 32.f ), SLOWEST_SPEED, Sprites::GetInstance()->GetSprite(BOMBER_JET_SRPITE), 20.f );
	}

	--m_iRatioOfEnemyTypes;
	m_iNumberOfEnemiesToSpawn += 2;

}

Vec2 Level::GetPlayerInfo()
{
	return Vec2( Player1->GetHealth(), Player1->GetLives() );
}

int Level::GetScore()
{
	return m_iScore;
}