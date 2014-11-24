#include "ActorLimb.h"

ActorLimb::ActorLimb( int a_iLimbID, Vec2 a_pSize, Vec2 a_pPos, int a_iTextureRow, bool a_bCenterOrigin )
{
	m_iLimbID = a_iLimbID;
	m_iTextureRow = a_iTextureRow;
	m_pPos = a_pPos;
	m_pSize = a_pSize;
	m_pMinUV = Vec2( 0.f,0.5f * (float)a_iTextureRow - 0.5f );
	m_pMaxUV = Vec2( 0.25f, 0.5f * (float)a_iTextureRow );
	m_bCenterDraw = a_bCenterOrigin;
	m_fCurrentRotation = 0.f;
	FaceDirection ( 100 ); 

}

ActorLimb::~ActorLimb()
{

}

void ActorLimb::FaceDirection( int a_iDirection )
{ 
	std::cout << a_iDirection << "\n";

	m_iDirection = a_iDirection;
	std::cout << m_iDirection << "\n";
}

void ActorLimb::SetOrigin()
{
	if( m_bCenterDraw )
	{
		Vertices[0].Pos = Vec4( -1.f, -1.f, 0.f, 1.f );
		Vertices[0].UV = Vec2( 0.f, 1.f );

		Vertices[1].Pos = Vec4( 1.f, -1.f, 0.f, 1.f );
		Vertices[1].UV = Vec2( 1.f, 1.f );

		Vertices[2].Pos = Vec4( -1.f, 1.f, 0.f, 1.f );
		Vertices[2].UV = Vec2( 0.f, 0.f );

		Vertices[3].Pos = Vec4( 1.f, 1.f, 0.f, 1.f );
		Vertices[3].UV = Vec2( 1.f, 0.f );
	}
	else
	{
		Vertices[0].Pos = Vec4( -0.5f, -0.5f, 0.f, 1.f );
		Vertices[0].UV = Vec2( 0.f, 1.f );

		Vertices[1].Pos = Vec4( 0.5f, -0.5f, 0.f, 1.f );
		Vertices[1].UV = Vec2( 1.f, 1.f );

		Vertices[2].Pos = Vec4( -0.5f, 0.5f, 0.f, 1.f );
		Vertices[2].UV = Vec2( 0.f, 0.f );

		Vertices[3].Pos = Vec4( 0.5f, 0.5f, 0.f, 1.f );
		Vertices[3].UV = Vec2( 1.f, 0.f );
	}
}

void ActorLimb::Draw( Vec2 a_pParentPos, GLuint a_uiShader, GLuint* a_uiTextures )
{
	std::cout << m_iDirection << "\n";
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	Matrix4 ModelMatrix = Matrix4(	m_pSize[0], 0.f, 0.f, 0.f, 
										0.f, m_pSize[1], 0.f, 0.f, 
											0.f, 0.f, 1.f, 0.f, 
												m_pPos[0] + a_pParentPos[0], m_pPos[1] + a_pParentPos[1], 0.f, 1.f );

	Matrix4 m4Rotate;
	m4Rotate.RotateMatrixZ( (float)Maths::DegToRad( m_fCurrentRotation ) );
	ModelMatrix = m4Rotate * ModelMatrix;

	
	switch( m_iDirection )
	{
	case DOWN_DIRECTION:
		m_pMinUV = Vec2( 0.f, 0.5f * (float)m_iTextureRow - 0.5f );
		m_pMaxUV = Vec2( 0.25f, 0.5f * (float)m_iTextureRow );
		break;

	case LEFT_DIRECTION:
		m_pMinUV = Vec2( 0.25f, 0.5f * (float)m_iTextureRow - 0.5f );
		m_pMaxUV = Vec2( 0.5f, 0.5f * (float)m_iTextureRow );
		break;
		
	case RIGHT_DIRECTION:
		m_pMinUV = Vec2( 0.5f, 0.5f * (float)m_iTextureRow - 0.5f );
		m_pMaxUV = Vec2( 0.75f, 0.5f * (float)m_iTextureRow );
		break;

	case UP_DIRECTION:
		m_pMinUV = Vec2( 0.75f, 0.5f * (float)m_iTextureRow - 0.5f );
		m_pMaxUV = Vec2( 1.f, 0.5f * (float)m_iTextureRow );
		break;

	default:
		break;
	}

	GLuint ModelID = glGetUniformLocation( a_uiShader,"Model" );
	glUniformMatrix4fv( ModelID, 1, false, ModelMatrix );
		
	GLuint minUV = glGetUniformLocation( a_uiShader, "minUV" );
	glUniform2fv( minUV, 1, m_pMinUV );

	GLuint diffUV = glGetUniformLocation( a_uiShader, "diffUV" );
	glUniform2fv( diffUV, 1, ( m_pMaxUV - m_pMinUV ) );

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, a_uiTextures[m_iLimbID] );
}

void ActorLimb::Update( float a_fRotation, Vec2 a_pPos )
{
	m_fCurrentRotation = a_fRotation;
	m_pPos = a_pPos;
}