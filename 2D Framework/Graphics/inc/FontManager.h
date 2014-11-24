////////////////////////////////////////////////////////////
// File: FontManager.h
// Author: Nick Smith
// Date Created: 17th June 2013
// Brief: Font Manager
////////////////////////////////////////////////////////////
#ifndef _FONT_MANAGER_H_
#define _FONT_MANAGER_H_

#include "Utilities.h"

class Font;

class DECLDIR FontManager
{
public:
	static void Create();
	static FontManager* Get();
	static void Delete();

	int NewFont( const char* a_ccFontFile );
	void SetFont( int a_iFontID );
	int GetFont();
	void DeleteFont( int a_iFontID );

	void DrawString( const char* a_ccText, Vec3 a_pPos, Vec4 a_pColour );
		
private:
	FontManager();
	~FontManager();

	void Initialise();

	int m_iNumFonts;
	std::vector<Font*> FontList;
	Font* m_pCurFont;

	static FontManager* m_pFontManager;
	
	FontVertex FontVertices[4];
	GLuint m_uiFontVAO;
	GLuint m_uiFontVBO;
	GLuint m_uiFontEBO;
	GLuint m_uiFontShaderProgram;
};

#endif // _FONT_MANAGER_H_