#include "Shapes.h"

#include "Window.h"

Shapes* Shapes::m_pInstance = nullptr;

Shapes* Shapes::Create()
{
	if( m_pInstance == nullptr )
	{
		m_pInstance = new Shapes();
	}

	return m_pInstance;
}

Shapes* Shapes::Get()
{
	return m_pInstance;
}

void Shapes::Delete()
{
	if( m_pInstance != nullptr )
	{
		delete m_pInstance;
	}
}

Shapes::Shapes()
{
	Init();
}

Shapes::~Shapes()
{
	glDeleteBuffers( 1, &m_uiCubeEBO );
	glDeleteBuffers( 1, &m_uiCubeVBO );
	glDeleteBuffers( 1, &m_uiLinesEBO );
	glDeleteBuffers( 1, &m_uiLinesVBO );
	glDeleteVertexArrays( 1, &m_uiCubeVAO );
	glDeleteVertexArrays( 1, &m_uiLinesVAO );

	glDeleteProgram( m_uiShaderProgram );
}

void Shapes::Init()
{
	glGenBuffers( 1, &m_uiLinesVBO );
	glGenBuffers( 1, &m_uiLinesEBO );
	glGenVertexArrays( 1, &m_uiLinesVAO );
	glGenBuffers( 1, &m_uiCubeVBO );
	glGenBuffers( 1, &m_uiCubeEBO );
	glGenVertexArrays( 1, &m_uiCubeVAO );
	m_uiShaderProgram = LoadShaders( "shaders/shapes-vertex-shader.glsl", "shaders/shapes-fragment-shader.glsl" );	

	glBindVertexArray( m_uiLinesVAO );	

	LinesVertices[0].Pos = Vec4( 0.f, 0.f, 0.f, 1.f );
	LinesVertices[0].Colour = Vec4( 0.f, 0.f, 0.f, 0.f );

	LinesVertices[1].Pos = Vec4( 1.f, 1.f, 0.f, 1.f );
	LinesVertices[1].Colour = Vec4( 0.f, 0.f, 0.f, 0.f );

	glBindBuffer( GL_ARRAY_BUFFER, m_uiLinesVBO );
	glBufferData( GL_ARRAY_BUFFER, 2 * sizeof( LineVertex ), LinesVertices, GL_STATIC_DRAW );

	GLuint elements[] = {
		0, 1
	};
		
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_uiLinesEBO );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( elements ), elements, GL_STATIC_DRAW );

	
	glUseProgram( m_uiShaderProgram );

	glBindFragDataLocation( m_uiShaderProgram, 0, "outColor" );

	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation( m_uiShaderProgram, "position" );
	glEnableVertexAttribArray( posAttrib );
	glVertexAttribPointer( posAttrib, 4, GL_FLOAT, GL_FALSE, sizeof( LineVertex ), 0 );

	GLint colAttrib = glGetAttribLocation( m_uiShaderProgram, "colour" );
	glEnableVertexAttribArray( colAttrib );	
	glVertexAttribPointer( colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof( LineVertex ), (void*)( sizeof( Vec4 ) ) );

	glBindVertexArray( 0 );

	GLuint ProjectionID = glGetUniformLocation( m_uiShaderProgram, "Projection" );
	GLuint ViewID = glGetUniformLocation( m_uiShaderProgram, "View" );

	glUniformMatrix4fv( ProjectionID, 1, false, (float*)Windows::Get()->GetWindow()->pProjection );
	glUniformMatrix4fv( ViewID, 1, false, (float*)Windows::Get()->GetWindow()->pView );
}

void Shapes::Render()
{
	// Create a struct for lines and other shapes, 
	// for now I just want lines for collision debugging
	glUseProgram( m_uiShaderProgram );
	
	GLuint ProjectionID = glGetUniformLocation( m_uiShaderProgram, "Projection" );
	glUniformMatrix4fv( ProjectionID, 1, false, (float*)Windows::Get()->GetWindow()->pProjection );

	while ( !LinesToDraw.empty() )
	{
		LineShape* pLine = LinesToDraw.front();
		if( pLine != NULL )
		{
			glBindVertexArray( m_uiLinesVAO );

			GLuint ModelID = glGetUniformLocation( m_uiShaderProgram, "Model" );
	
			Matrix4 ModelMatrix = Matrix4( pLine->End[0] - pLine->Start[0], 0.f, 0.f, 0.f, 
											 0.f, pLine->End[1] - pLine->Start[1], 0.f, 0.f, 
											  0.f, 0.f, 1.f, 0.f, 
											  pLine->Start[0], pLine->Start[1], 0.f, 1.f );

			glUniformMatrix4fv( ModelID, 1, false, ModelMatrix );

			GLuint TintID = glGetUniformLocation( m_uiShaderProgram, "vTintColour" );
			glUniform4fv( TintID, 1, pLine->Colour );

			glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);

			glBindVertexArray( 0 );
		}
		LinesToDraw.pop();
	}

	glUseProgram( 0 );

}

void Shapes::DrawLine( Vec2 a_pStart, Vec2 a_pEnd, Vec4 a_pColour )
{
	LineShape* line = new LineShape;
	line->Start = a_pStart;
	line->End = a_pEnd;
	line->Colour = a_pColour;

	LinesToDraw.push( line );
}