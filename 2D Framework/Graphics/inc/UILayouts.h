////////////////////////////////////////////////////////////
// File: UILayouts.h
// Author: Nick Smith
// Date Created: 1st July 2013
// Brief: UI layouts manager
////////////////////////////////////////////////////////////

#ifndef _UI_LAYOUTS_H_
#define _UI_LAYOUTS_H_

#include "Utilities.h"
#include "UIElements.h"

struct Layout
{
	int ID;
	GLuint LayoutBG;
	Vec2 LayoutPos;
	Vec2 LayoutSize;

	std::vector<UIElement*> LayoutElements;
};

class DECLDIR UILayouts
{
public:
	static UILayouts* Create();
	static UILayouts* Get();
	static void Delete();

	int LoadLayout( const char* a_ccLayoutFile );
	void Update();
	void Render();
	void SetLayout( int a_iLayoutID );
	void ToggleDrawLayout( bool a_bToggle );


	// Element specific functions
	// buttons
	void SetButtonEvent( int a_iElementID, std::function<void()> ClickFunction );

	// labels
	void SetLabelVariable( int a_iElementID, int a_iType, void* p );

	// meters
	void SetMeterVariable( int a_iElementID, void* p );
	void SetMeterFunction( int a_iElementID, void ( *p )() );
	void SetMeterMinMax( int a_iElementID, Vec2 a_pValues );

protected:
	UILayouts();
	~UILayouts();
private:
	void Init();

	Vec2 m_pSize;
	Vec2 m_pPos;

	static UILayouts* m_pInstance;

	Layout* m_pCurLayout;
	bool m_bDraw;

	std::vector<Layout*> Layouts;
	int m_iNumLayouts;

	Vertex Vertices[4];

	GLuint m_uiLVAO;
	GLuint m_uiLVBO;
	GLuint m_uiLEBO;
	GLuint m_uiLFBO;
	GLuint m_uiUIImage;
	GLuint m_uiLayoutShader;
};


#endif //_UI_LAYOUTS_H_