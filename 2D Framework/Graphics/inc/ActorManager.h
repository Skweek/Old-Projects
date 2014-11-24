////////////////////////////////////////////////////////////
// File: ActorManager.h
// Author: Nick Smith
// Date Created: 2nd September 2013
// Brief: Manages all actors
////////////////////////////////////////////////////////////
#ifndef _ACTOR_MANAGER_H_
#define _ACTOR_MANAGER_H_

#include "Utilities.h"

void InitActorManager();
void DeInitActorManager();

int NewActor( const char* a_ccFile, Vec2 a_pPos );
void AddActorToDrawQueue( int a_iID );
void DeleteActor( int a_iID );
void UpdateActor( int a_iID, Vec2 a_pPos );

void ActorFaceDirection( int a_iID, int a_iDirection );

void ReloadActors();

void RenderAllActors();

#endif //_ACTOR_MANAGER_H_