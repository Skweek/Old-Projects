#include "EnemyManager.h"

#include "FighterJet.h"
#include "BomberJet.h"
#include "Level.h"
#include "Collision.h"

EnemyManager::EnemyManager()
{
	EnemyList.clear();
}

void EnemyManager::CreateEnemy( int a_iEnemyType, Vec2 a_pPosition, Vec2 a_uiSize, int a_iSpeed, unsigned int a_iSprite, float a_fHealth )
{
	switch ( a_iEnemyType )
	{
	case BOMBER_JET_ENEMY:
		{
			BomberJet* bomber = new BomberJet( a_pPosition, a_uiSize, a_iSpeed, a_iSprite, a_fHealth );
			EnemyList.push_back( bomber );
		}
		break;

	case FIGHTER_JET_ENEMY:
		{
			FighterJet* fighter = new FighterJet( a_pPosition, a_uiSize, a_iSpeed, a_iSprite, a_fHealth );
			EnemyList.push_back( fighter );
		}
		break;

	default:
		break;
	}

}

void EnemyManager::DeleteEnemy( Enemy* a_pEnemy )
{
	std::vector<Enemy*>::iterator pIter = EnemyList.begin();
	for(std::vector<Enemy*>::iterator pIter = EnemyList.begin() ; pIter != EnemyList.end(); ++pIter)
	{
		Enemy* pEnemy = (*pIter);	
		if ( pEnemy == a_pEnemy )
		{				
			delete pEnemy;
			EnemyList.erase( pIter );
			break;
		}
	}
}

void EnemyManager::Update( float a_fDelta, Level* LevelHandle )
{
	for ( int i = 0; i < (int)EnemyList.size() - 1; ++i )
	{
		Enemy* e = EnemyList[i];
		e->Update( a_fDelta, LevelHandle );

		if ( e->GetHealth() <= 0.f )
		{
    			DeleteEnemy( e );
		}
	}
}

void EnemyManager::OnCollision( Enemy* a_iEnemy, int a_iEffect, int a_iModifier )
{
	std::vector<Enemy*>::iterator pIter = EnemyList.begin();
	for( ; pIter != EnemyList.end(); )
	{
		Enemy* pEnemy = (*pIter);	
		if ( pEnemy == a_iEnemy )
		{				
			pEnemy->OnCollision( a_iEffect, a_iModifier );
		}
		break;
	}
}

Vec2 EnemyManager::GetEnemyPosition( Enemy* a_iEnemy )
{
	return a_iEnemy->GetPos();
}

Vec2 EnemyManager::GetEnemySize( Enemy* a_iEnemy )
{
	return a_iEnemy->GetSize();
	
}

void EnemyManager::SetEnemyPosition( Enemy* a_iEnemy, Vec2 a_pPos )
{
	a_iEnemy->SetPos( a_pPos );
}

void EnemyManager::SetEnemySize( Enemy* a_iEnemy, Vec2 a_pSize )
{		
	a_iEnemy->SetPos( a_pSize);
}

bool EnemyManager::CheckCollision( Vec2 a_pBulletPos, Vec2 a_pBulletSize, int a_iDamage )
{
	for (std::vector<Enemy*>::iterator pIter = EnemyList.begin() ; pIter != EnemyList.end(); ++pIter)
	{
		Enemy* pEnemy = (*pIter);	
		
		// Add 5 to bullet size to make sure it hits even if it is just an edge collision
         if( Collision::CheckBoxCollision( a_pBulletPos, a_pBulletSize + Vec2( 5.f, 5.f ), pEnemy->GetPos(), pEnemy->GetSize() ) )
		{
			pEnemy->OnCollision( TAKE_DAMAGE_EFFECT, a_iDamage );
			return true;
		}
		else
		{
			continue;
		}
	}
	return false;
}