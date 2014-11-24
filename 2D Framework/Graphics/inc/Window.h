////////////////////////////////////////////////////////////
// File: Window.h
// Author: Nick Smith
// Date Created: 28th May 2013
// Brief: Window Handling
////////////////////////////////////////////////////////////

#ifndef _WINDOWS_H_
#define _WINDOWS_H_


#include "Utilities.h"

class DECLDIR Windows
{
	enum WindowShapes
	{
		STANDARD_WINDOW,
		TRIANGLE_WINDOW,
		CIRCLE_WINDOW,
		Z_WINDOW,

		// Window count
		WINDOW_COUNT
	};

public:
	struct Window
	{
		Window()
		{

		}

		GLFWwindow*		windowHandle;
		GLEWContext*	glewContext;
		Vec2			pWindowSize;
		Matrix4			pCamera;
		Matrix4			pProjection;
		Matrix4			pView;

		ScreenQuadrant m_pScreenQuadrants[4];

		int				windowID;
	};

	static Windows* Create();
	static Windows* Get();
	static void Delete();

	int CreateNewWindow( float* a_fSize, float* a_fPos, int a_iWindowID, 
						const char* a_ccWindowTitle = "", int a_iShare = NULL );
	void DeleteWindow( int a_iWindowID );
	void SetWindowFocus( int a_iWindowID );

	void UpdateWindows();
	void SetWindowTitle( int a_iWindowID, const char* a_ccTitle );
	void SetWindowShape( int a_iWindowID, int a_iWindowShape );
	void SetWindowShape( int a_iWindowID, float* a_fWindowPoints );
	void SetWindowAlpha( int a_iWindowID, float a_fOpacity );
	void SetWindowPos( int a_iWindowID, float* a_fPos );

	GLFWwindow* GetCurrentActiveWindow();

	ScreenQuadrant* GetCurrentQuadrant( float a_fX, float a_fY );

#pragma region inline functions
	static inline void WindowResize( GLFWwindow* a_pWindow, int a_iWidth, int a_iHeight )
	{
		a_pWindow;
		glViewport(0, 0, a_iWidth, a_iHeight);
	}

	inline GLEWContext* GetGLEWContext()
	{
		if( !CurrentWindow ) return NULL;
		return CurrentWindow->glewContext;
	}
	
	inline GLEWContext* glewGetContext()
	{
		if( !CurrentWindow ) return NULL;
		return CurrentWindow->glewContext;
	}
	
	inline Window* GetWindow()
	{
		return CurrentWindow;
	}

	inline int WindowShouldClose()
	{
		return glfwWindowShouldClose( CurrentWindow->windowHandle );
	}

#pragma endregion

private:
	inline void MakeContextCurrent( Window* a_pWindow )
	{
		CurrentWindow = a_pWindow;
		glfwMakeContextCurrent( a_pWindow->windowHandle );
	}
	
	Window* CurrentWindow;

	Windows();
	~Windows();
	
	std::vector<Window*> WindowList;

	static Windows* m_pInstance;

	float** windowPoints;

	
};

#endif // _WINDOWS_H_