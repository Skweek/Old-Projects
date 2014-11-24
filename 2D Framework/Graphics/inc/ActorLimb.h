////////////////////////////////////////////////////////////
// File: ActorLimb.h
// Author: Nick Smith
// Date Created: 2nd September 2013
// Brief: Game Actor Limb class
////////////////////////////////////////////////////////////
#ifndef _ACTOR_LIMB_H_
#define _ACTOR_LIMB_H_

#include "Utilities.h"

class ActorLimb
{
public:
	ActorLimb( int a_iLimbID, Vec2 a_pSize, Vec2 a_pPos, int a_iTextureRow, bool a_bCenterOrigin = false );
	~ActorLimb();
	
	void Draw( Vec2 a_pParentPos, GLuint a_uiShader, GLuint* a_uiTextures );
	void Update( float a_fRotation, Vec2 a_pPos );

	void FaceDirection( int a_iDirection );
	
	inline Vertex* GetVertices()
	{
		return Vertices;
	}

private:
	void SetOrigin();

	GLuint m_uiImage;
	Vertex Vertices[4];
	
	int m_iLimbID;
	int m_iDirection;
	int m_iTextureRow;
	Vec2 m_pPos; // Position is relative to parent Actor
	Vec2 m_pSize;
	Vec2 m_pMinUV;
	Vec2 m_pMaxUV;
	bool m_bCenterDraw; // Point that Limb rotates around

	float m_fCurrentRotation;
};

#endif //_ACTOR_LIMB_H_