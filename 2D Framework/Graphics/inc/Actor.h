////////////////////////////////////////////////////////////
// File: Actor.h
// Author: Nick Smith
// Date Created: 2nd September 2013
// Brief: Game Actor class
////////////////////////////////////////////////////////////
#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "Utilities.h"

class ActorLimb;

class Actor
{
public:
	Actor( const char* a_ccFile, Vec2 a_pPos );
	~Actor();

	void Draw( GLuint a_uiShader, GLuint VBO, GLuint VAO, GLuint* a_uiTextures );
	void ReloadActor();

	void FaceDirection( int a_iDirection );

	inline void Move( Vec2 a_pPos )
	{
		m_pPos = a_pPos;
	}

private:
	void LoadActor(  const char* a_ccFile );

	Vec2 m_pPos;
	const char* m_ccActorFile;
	std::vector<ActorLimb> m_pParts;

	// This stuff is to deal with real time reloading of actors
	// It is only supported on windows and so that needs to be dealt with
	FILETIME m_FTLastModdified;
};

#endif //_ACTOR_H_