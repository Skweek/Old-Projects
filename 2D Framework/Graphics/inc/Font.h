////////////////////////////////////////////////////////////
// File: Font.h
// Author: Nick Smith
// Date Created: 17th June 2013
// Brief: Font structure
////////////////////////////////////////////////////////////
#ifndef _FONT_H_
#define _FONT_H_

#include "Utilities.h"

class DECLDIR Font
{
public:
	Font();
	Font( const char* a_ccFont, int a_iFontID );
	~Font();

	friend class FontManager;

protected:
	int m_iFontID;

	bool LoadFont( const char* a_ccFontFile, int a_iFontID );

	const char* m_ccFontFace;
	GLuint m_uiFontTexture;

	int m_iSize;
	int m_iNumCharacters;
	Character* m_pCharacterList;

	bool m_bBold;
	bool m_bItalic;
	bool m_bUnicode;

	int m_iStretchH;
	int m_iSmooth;
	int m_iAA;

	int m_iOutline;

	int m_iLineHeight;
	int m_iBase;
	int m_iScaleW;
	int m_iScaleH;
	int m_iPacked;
	Vec4 m_pChannels;
};

#endif // _FONT_H_