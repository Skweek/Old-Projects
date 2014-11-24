////////////////////////////////////////////////////////////
// File: UIElements.h
// Author: Nick Smith
// Date Created: 1st July 2013
// Brief: UI elements classes
////////////////////////////////////////////////////////////

#ifndef _UI_ELEMENTS_H_
#define _UI_ELEMENTS_H_

#include "Utilities.h"

// Base UI Element
class DECLDIR UIElement
{
public:
	UIElement( Vec2 a_pPos, Vec2 a_pSize, int a_iID );
	~UIElement();

	virtual void Draw( GLuint m_uiShader ) = 0;
	virtual void Update() = 0;

	friend class UILayouts;

protected:
	Vec2 m_pSize;
	Vec2 m_pPos;

	int m_iID;
};

// Button Element
class UIButton : public UIElement
{
public:
	UIButton( Vec2 a_pPos, Vec2 a_pSize, int a_iID, const char* a_ccImageUp, const char* a_ccImageDown );
	~UIButton();

	void SetClickFunction( std::function<void()> function );

protected:
	void Draw( GLuint m_uiShader );
	void Update();

	bool OnClick( Vec2 a_pMousePos );
	std::function<void()> ClickFunction;

	bool m_bPressed;
	Vec4 m_pClickable;
	GLuint m_uiImageUp;
	GLuint m_uiImageDown;

	int m_iButtonState;
};

// Label Element
class UILabel : public UIElement
{
public:
	UILabel( Vec2 a_pPos, int a_iID, std::string a_ccText, Vec4 a_pTextColour = Vec4( 0.f, 0.f, 0.f, 1.f ) );
	~UILabel();

	void SetText( const char* a_ccText );
	void SetTextColour( Vec4 a_pColour );

	void SetVariablePointer( int a_iType, void* p );

protected:
	void Draw( GLuint m_uiShader );
	void Update();

	void* m_pVarPointer;

	int m_iVarType;

	std::string m_ccText;
	Vec4 m_pTextColour;
};

// Meter Element
class UIMeter : public UIElement
{
public:
	UIMeter( Vec2 a_pPos, Vec2 a_pSize, int a_iID, const char* a_ccMeterImageFile, 
				const char* a_ccBGImageFile, float* a_fMeterPadding );
	~UIMeter();

	void SetValue( float a_fValue );
	float GetValue();

	void SetMin( float a_fMin );
	void SetMax( float a_fMax );

	void SetMeterVariable( void* p );
	void SetMeterFunction( void ( *p )() );

protected:
	void Draw( GLuint m_uiShader );	
	void Update();

	void* m_fMeterVariable;
	float m_fMinValue;
	float m_fMaxValue;
	float m_fCurValue;

	void ( *MeterFunction)();

	GLuint m_uiMeterImage;
	GLuint m_uiBGImage;

	Vec2 m_pMeterSize;
	Vec2 m_pMeterPos;

};

#endif //_UI_ELEMENTS_H_