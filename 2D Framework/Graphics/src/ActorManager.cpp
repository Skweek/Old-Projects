#include "ActorManager.h"
#include "Actor.h"
#include "Window.h"

std::vector<Actor*> ActorsList;
std::queue<Actor*> ActorsToDraw;
	
Vertex Vertices[4];

GLuint m_uiVAO;
GLuint m_uiVBO;
GLuint m_uiEBO;
GLuint m_uiShaderProgram;

GLuint m_uiActorTextures[6];

void InitActorManager()
{
	// Gen Buffers
	glGenBuffers( 1, &m_uiVBO );
	glGenBuffers( 1, &m_uiEBO );
	glGenVertexArrays( 1, &m_uiVAO );

	m_uiShaderProgram = LoadShaders( "shaders/sprite-vertex-shader.glsl", "shaders/sprite-fragment-shader.glsl" );	

	m_uiActorTextures[0] = LoadTexture("images/sprites/ActorArmLeft.png");
	m_uiActorTextures[1] = LoadTexture("images/sprites/ActorArmRight.png");
	m_uiActorTextures[2] = LoadTexture("images/sprites/ActorLegLeft.png");
	m_uiActorTextures[3] = LoadTexture("images/sprites/ActorLegRight.png");
	m_uiActorTextures[4] = LoadTexture("images/sprites/ActorBody.png");
	m_uiActorTextures[5] = LoadTexture("images/sprites/ActorHeadHair.png");

	glBindVertexArray( m_uiVAO );

	Vertices[0].Pos = Vec4( -1.f, -1.f, 0.f, 1.f );
	Vertices[0].UV = Vec2( 0.f, 1.f );

	Vertices[1].Pos = Vec4( 1.f, -1.f, 0.f, 1.f );
	Vertices[1].UV = Vec2( 1.f, 1.f );

	Vertices[2].Pos = Vec4( -1.f, 1.f, 0.f, 1.f );
	Vertices[2].UV = Vec2( 0.f, 0.f );

	Vertices[3].Pos = Vec4( 1.f, 1.f, 0.f, 1.f );
	Vertices[3].UV = Vec2( 1.f, 0.f );

	glBindBuffer( GL_ARRAY_BUFFER, m_uiVBO );
	glBufferData( GL_ARRAY_BUFFER, 4 * sizeof( Vertex ), Vertices, GL_STATIC_DRAW );

	GLuint elements[] = {
		0, 1, 2,
		1, 3, 2
	};

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_uiEBO );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( elements ), elements, GL_STATIC_DRAW );

	glUseProgram( m_uiShaderProgram );
		
	glBindFragDataLocation( m_uiShaderProgram, 0, "outColor" );
			
	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation( m_uiShaderProgram, "position" );
	glEnableVertexAttribArray( posAttrib );
	glVertexAttribPointer( posAttrib, 4, GL_FLOAT, GL_FALSE, sizeof( Vertex ), 0 );

	GLint texAttrib = glGetAttribLocation( m_uiShaderProgram, "texcoord" );
	glEnableVertexAttribArray( texAttrib );
	glVertexAttribPointer( texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*)( sizeof( Vec4 ) ) );

	glBindVertexArray( 0 );

	Matrix4 iden = Matrix4( 1.f, 0.f, 0.f, 0.f, 
							 0.f, 1.f, 0.f, 0.f, 
							  0.f, 0.f, 1.f, 0.f, 
							   0.f, 0.f, 0.f, 1.f );

	GLuint ProjectionID = glGetUniformLocation( m_uiShaderProgram, "Projection" );
	GLuint ViewID = glGetUniformLocation( m_uiShaderProgram, "View" );

	glUniformMatrix4fv( ProjectionID, 1, false, (float*)Windows::Get()->GetWindow()->pProjection );
	glUniformMatrix4fv( ViewID, 1, false, (float*)Windows::Get()->GetWindow()->pView );
}

void DeInitActorManager()
{
	std::vector<Actor*>::iterator pIter = ActorsList.begin();
	for( ; pIter < ActorsList.end();  )
	{
		Actor* pActor = (*pIter);
		delete pActor;
		pIter = ActorsList.erase(pIter);
	}

	glDeleteBuffers( 1, &m_uiVBO );
	glDeleteBuffers( 1, &m_uiEBO );
	glDeleteVertexArrays( 1, &m_uiVAO );
	glDeleteProgram( m_uiShaderProgram );
}

void ReloadActors()
{
	for( int i = 0; i < ActorsList.size(); ++i )
	{
		ActorsList[i]->ReloadActor();
	}
}

void RenderAllActors()
{
	GLuint ProjectionID = glGetUniformLocation( m_uiShaderProgram, "Projection" );
	glUniformMatrix4fv( ProjectionID, 1, false, (float*)Windows::Get()->GetWindow()->pProjection );

	while ( !ActorsToDraw.empty() )
	{
		Actor* pActor = ActorsToDraw.front();
		if( pActor != NULL )
		{
			pActor->Draw( m_uiShaderProgram, m_uiVBO, m_uiVAO, m_uiActorTextures );
		}
		ActorsToDraw.pop();
	}
	glUseProgram( 0 );
}

int NewActor( const char* a_ccFile, Vec2 a_pPos )
{
	Actor* tempActor = new Actor( a_ccFile, a_pPos );
	ActorsList.push_back( tempActor );

	return ActorsList.size() - 1;
}

void DeleteActor( int a_iID )
{
	a_iID;
}

void ActorFaceDirection( int a_iID, int a_iDirection )
{
	ActorsList[a_iID]->FaceDirection( a_iDirection );
}

void AddActorToDrawQueue( int a_iID )
{
	ActorsToDraw.push( ActorsList[a_iID] );
}

void UpdateActor( int a_iID, Vec2 a_pPos )
{
	ActorsList[a_iID]->ReloadActor();
	ActorsList[a_iID]->Move( a_pPos );
}