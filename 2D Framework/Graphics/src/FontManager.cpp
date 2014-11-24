#include "FontManager.h"

#include "Font.h"
#include "Window.h"

FontManager* FontManager::m_pFontManager;

void FontManager::Create()
{
	delete m_pFontManager;

	m_pFontManager = new FontManager;
}

FontManager* FontManager::Get()
{
	if( !m_pFontManager )
	{
		m_pFontManager = new FontManager;
	}
	
	return m_pFontManager;
}

void FontManager::Delete()
{
	delete m_pFontManager;
}

FontManager::FontManager()
{
	FontList.clear();
	m_iNumFonts = 0;
	Initialise();
}

FontManager::~FontManager()
{
	std::vector<Font*>::iterator pIter = FontList.begin();
	for( ; pIter < FontList.end();  )
	{
		Font* pFont = (*pIter);
		delete pFont;
		pIter = FontList.erase(pIter);
	}
	FontList.clear();

	glDeleteProgram( m_uiFontShaderProgram );
	glDeleteBuffers( 1, &m_uiFontVBO );
	glDeleteBuffers( 1, &m_uiFontEBO );
	glDeleteVertexArrays( 1, &m_uiFontVAO );
}

void FontManager::Initialise()
{	
	glGenBuffers( 1, &m_uiFontVBO );
	glGenBuffers( 1, &m_uiFontEBO );
	glGenVertexArrays( 1, &m_uiFontVAO );
	m_uiFontShaderProgram = LoadShaders( "shaders/font-vertex-shader.glsl", "shaders/font-fragment-shader.glsl" );	

	glBindVertexArray( m_uiFontVAO );	

	FontVertices[0].Pos = Vec4( 0.f, 0.f, 0.f, 1.f );
	FontVertices[0].UV = Vec2( 0.f, 1.f );
	FontVertices[0].Colour = Vec4( 0.f, 0.f, 0.f, 0.f );

	FontVertices[1].Pos = Vec4( 1.f, 0.f, 0.f, 1.f );
	FontVertices[1].UV = Vec2( 1.f, 1.f );
	FontVertices[1].Colour = Vec4( 0.f, 0.f, 0.f, 0.f );

	FontVertices[2].Pos = Vec4( 0.f, 1.f, 0.f, 1.f );
	FontVertices[2].UV = Vec2( 0.f, 0.f );
	FontVertices[2].Colour = Vec4( 0.f, 0.f, 0.f, 0.f );

	FontVertices[3].Pos = Vec4( 1.f, 1.f, 0.f, 1.f );
	FontVertices[3].UV = Vec2( 1.f, 0.f );
	FontVertices[3].Colour = Vec4( 0.f, 0.f, 0.f, 0.f );

	glBindBuffer( GL_ARRAY_BUFFER, m_uiFontVBO );
	glBufferData( GL_ARRAY_BUFFER, 4 * sizeof( FontVertex ), FontVertices, GL_STATIC_DRAW );

	GLuint elements[] = {
		0, 1, 2,
		1, 3, 2
	};
		
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_uiFontEBO );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( elements ), elements, GL_STATIC_DRAW );

	glUseProgram( m_uiFontShaderProgram );

	glBindFragDataLocation( m_uiFontShaderProgram, 0, "outColor" );

	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation( m_uiFontShaderProgram, "position" );
	glEnableVertexAttribArray( posAttrib );
	glVertexAttribPointer( posAttrib, 4, GL_FLOAT, GL_FALSE, sizeof( FontVertex ), 0 );

	GLint texAttrib = glGetAttribLocation( m_uiFontShaderProgram, "texcoord" );
	glEnableVertexAttribArray( texAttrib );
	glVertexAttribPointer( texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof( FontVertex ), (void*)( sizeof( Vec4 ) ) );

	GLint colAttrib = glGetAttribLocation( m_uiFontShaderProgram, "colour" );
	glEnableVertexAttribArray( colAttrib );	
	glVertexAttribPointer( colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof( FontVertex ), (void*)( sizeof( Vec4 ) + sizeof( Vec2 ) ) );

	glBindVertexArray( 0 );

	GLuint ProjectionID = glGetUniformLocation( m_uiFontShaderProgram, "Projection" );
	GLuint ViewID = glGetUniformLocation( m_uiFontShaderProgram, "View" );

	glUniformMatrix4fv( ProjectionID, 1, false, (float*)Windows::Get()->GetWindow()->pProjection );
	glUniformMatrix4fv( ViewID, 1, false, (float*)Windows::Get()->GetWindow()->pView );
}

int FontManager::NewFont( const char* a_ccFontFile )
{
	Font* pFont = new Font( a_ccFontFile, ++m_iNumFonts );

	FontList.push_back( pFont );

	m_pCurFont = pFont;

	return m_iNumFonts;
}

void FontManager::DrawString( const char* a_ccText, Vec3 a_pPos, Vec4 a_pColour )
{
	glUseProgram( m_uiFontShaderProgram );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	GLuint ProjectionID = glGetUniformLocation( m_uiFontShaderProgram, "Projection" );
	glUniformMatrix4fv( ProjectionID, 1, false, (float*)Windows::Get()->GetWindow()->pProjection );

	glBindTexture( GL_TEXTURE_2D, m_pCurFont->m_uiFontTexture );
	if( a_ccText != NULL )
	{
		int iSize = strlen( a_ccText );
		int iFirstID = m_pCurFont->m_pCharacterList[0].id;
		for( int c = 0; c < iSize; ++c )
		{
			int iCurChar = a_ccText[c] - iFirstID;			
			Character* pChar = &m_pCurFont->m_pCharacterList[iCurChar];	
			
			FontVertices[0].Pos = Vec4( a_pPos[0], a_pPos[1], a_pPos[2], 1.f );
			FontVertices[0].UV = Vec2( (float)pChar->x / m_pCurFont->m_iScaleW,						
										(float)( pChar->y + pChar->height ) / m_pCurFont->m_iScaleH );
			FontVertices[0].Colour = a_pColour;

			FontVertices[1].Pos = Vec4( (float)a_pPos[0] + pChar->width,				
											(float)a_pPos[1], 0.f, 1.f );
			FontVertices[1].UV = Vec2( ( (float)pChar->x + pChar->width ) / m_pCurFont->m_iScaleW,	
											(float)( pChar->y + pChar->height ) / m_pCurFont->m_iScaleH );
			FontVertices[1].Colour = a_pColour;

			FontVertices[2].Pos = Vec4( a_pPos[0],										
										(float)a_pPos[1] - pChar->height, 0.f, 1.f );
			FontVertices[2].UV = Vec2( (float)pChar->x / m_pCurFont->m_iScaleW,						
										(float)( pChar->y ) / m_pCurFont->m_iScaleH );
			FontVertices[2].Colour = a_pColour;

			FontVertices[3].Pos = Vec4( (float)a_pPos[0] + pChar->width,				
										(float)a_pPos[1] - pChar->height, 0.f, 1.f );
			FontVertices[3].UV = Vec2( (float)( pChar->x + pChar->width ) / m_pCurFont->m_iScaleW,	
										(float)( pChar->y ) / m_pCurFont->m_iScaleH );
			FontVertices[3].Colour = a_pColour;

			GLuint ModelID = glGetUniformLocation( m_uiFontShaderProgram, "Model" );
	
			Matrix4 ModelMatrix = Matrix4( 1.f, 0.f, 0.f, 0.f, 
											 0.f, 1.f, 0.f, 0.f, 
											  0.f, 0.f, 1.f, 0.f, 
											   0.f, 0.f, 0.f, 1.f );

			glUniformMatrix4fv( ModelID, 1, false, ModelMatrix );
			
			glBindBuffer( GL_ARRAY_BUFFER, m_uiFontVBO );
			glBufferSubData( GL_ARRAY_BUFFER, 0, 4 * sizeof( FontVertex ), FontVertices );

			glBindVertexArray( m_uiFontVAO );

			glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

			a_pPos.m_fX += pChar->xAdvance;
		}
	}
	
	glUseProgram( 0 );
	glBindTexture( GL_TEXTURE_2D, 0 );
	glBindVertexArray( 0 );
}

void FontManager::SetFont( int a_iFontID )
{
	for( int i = 0; i < (int)FontList.size(); ++i )
	{
		Font* font = FontList[i];
		if( font->m_iFontID == a_iFontID )
		{
			m_pCurFont = font;
		}
	}
}

int FontManager::GetFont()
{
	return m_pCurFont->m_iFontID;
}