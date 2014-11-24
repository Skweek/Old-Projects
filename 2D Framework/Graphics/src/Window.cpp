#include "Window.h"
#include "WindowShapes.h"
#include "Scripts.h" // For getting window information

Windows* Windows::m_pInstance = nullptr;

Windows* Windows::Create()
{
	if( !m_pInstance )
	{
		m_pInstance = new Windows();
	}

	return m_pInstance;
}

Windows* Windows::Get()
{
	if( !m_pInstance )
	{
		m_pInstance = new Windows();
	}

	return m_pInstance;
}

void Windows::Delete()
{
	if( m_pInstance )
	{
		delete m_pInstance;
	}
}

Windows::Windows()
{
	WindowList.clear();	
}

Windows::~Windows()
{
	while( !WindowList.empty() )
	{
		std::vector<Window*>::iterator pIter = WindowList.begin();
		Window* pWindow = (*pIter);
		glfwDestroyWindow( pWindow->windowHandle );
		WindowList.erase( pIter );
	}
	WindowList.clear();
}

int Windows::CreateNewWindow( float* a_fSize, float* a_fPos, int a_iWindowID, 
	const char* a_ccWindowTitle, int a_iShare )
{
	a_fSize;

	Window* NewWindow = new Window;

	NewWindow->windowID = a_iWindowID;
	NewWindow->glewContext = new GLEWContext();

	NewWindow->pWindowSize = GetScreenResolution();

	NewWindow->pCamera.Camera( Vec4( 0, 0, 0, 1 ), Vec4( 0, 0, 1, 0 ), Vec4( 0, 1, 0, 0 ) );
	NewWindow->pProjection.Ortho( 0.f, NewWindow->pWindowSize[0], 0.f, NewWindow->pWindowSize[1], 0.f, 100.f );
	NewWindow->pView = NewWindow->pCamera.LookAt();

	if( a_iShare == NULL )
	{
		NewWindow->windowHandle = glfwCreateWindow( (int)NewWindow->pWindowSize[0], (int)NewWindow->pWindowSize[1], "Simple example", NULL, NULL );
	}
	else if( a_iShare != NULL )
	{
		std::vector<Window*>::iterator pIter = WindowList.begin();
		for( ; pIter != WindowList.end(); ++pIter)
		{
			Window* pWindow = (*pIter);	
			if( pWindow->windowID == a_iShare )
			{				
				NewWindow->windowHandle = glfwCreateWindow( (int)NewWindow->pWindowSize[0], (int)NewWindow->pWindowSize[1], "Simple example", glfwGetPrimaryMonitor(), pWindow->windowHandle );
				break;
			}
		}
	}

	glfwSetWindowTitle( NewWindow->windowHandle, a_ccWindowTitle );

	glfwSetWindowPos( NewWindow->windowHandle, (int)a_fPos[0], (int)a_fPos[1] );

	glfwSetWindowSizeCallback( NewWindow->windowHandle, WindowResize );

	// Set this window to current so that GLEW can
	// be initialised
	glfwMakeContextCurrent( NewWindow->windowHandle );
	CurrentWindow = NewWindow;
	
	// Init GLEW
	glewExperimental = 1;
	if( glewInit() != 0 )
	{		
		std::cout << "Initialise GLEW: " << glGetError() << std::endl;
	}
	
	// Set up screen quadrants
	// Top Left Quad
	NewWindow->m_pScreenQuadrants[0] = ScreenQuadrant( 1, Vec2( 0.f, 0.f ), 
														Vec2 ( NewWindow->pWindowSize[0] / 2, NewWindow->pWindowSize[1] / 2 ) ); 
	// Top Right Quad
	NewWindow->m_pScreenQuadrants[1] = ScreenQuadrant( 2, Vec2 ( 0.f, NewWindow->pWindowSize[1] / 2 ), 
														Vec2 ( NewWindow->pWindowSize[0] / 2, NewWindow->pWindowSize[1] / 2 ) );
	// Bottom Left Quad
	NewWindow->m_pScreenQuadrants[2] = ScreenQuadrant( 3, Vec2 ( NewWindow->pWindowSize[0] / 2, 0.f ), 
														Vec2 ( NewWindow->pWindowSize[0] / 2, NewWindow->pWindowSize[1] / 2 ) ); 
	// Bottom Right Quad
	NewWindow->m_pScreenQuadrants[3] = ScreenQuadrant( 4, Vec2 ( NewWindow->pWindowSize[0] / 2, NewWindow->pWindowSize[1] / 2 ), 
														Vec2 ( NewWindow->pWindowSize[0] / 2, NewWindow->pWindowSize[1] / 2 ) ); 

	glViewport( 0, 0, (int)NewWindow->pWindowSize[0], (int)NewWindow->pWindowSize[1] );

	WindowList.push_back( NewWindow );

	return a_iWindowID;
}

void Windows::DeleteWindow( int a_iWindowID )
{
	std::vector<Window*>::iterator pIter = WindowList.begin();
	for( ; pIter != WindowList.end(); ++pIter)
	{
		Window* pWindow = (*pIter);	
		if( pWindow->windowID == a_iWindowID )
		{				
			glfwDestroyWindow( pWindow->windowHandle );
			WindowList.erase( pIter );
			break;
		}
	}
}

void Windows::SetWindowTitle( int a_iWindowID, const char* a_ccTitle) 
{
	std::vector<Window*>::iterator pIter = WindowList.begin();
	for( ; pIter != WindowList.end(); ++pIter)
	{
		Window* pWindow = (*pIter);	
		if( pWindow->windowID == a_iWindowID )
		{				
			glfwSetWindowTitle( pWindow->windowHandle, a_ccTitle );
			break;
		}
	}
}

void Windows::SetWindowFocus( int a_iWindowID )
{
	std::vector<Window*>::iterator pIter = WindowList.begin();
	for( ; pIter != WindowList.end(); ++pIter)
	{
		Window* pWindow = (*pIter);	
		if( pWindow->windowID == a_iWindowID )
		{				
			glfwMakeContextCurrent( pWindow->windowHandle );
			CurrentWindow = pWindow;
			break;
		}
	}
}

void Windows::SetWindowPos( int a_iWindowID, float* a_fPos )
{
	std::vector<Window*>::iterator pIter = WindowList.begin();
	for( ; pIter != WindowList.end(); ++pIter)
	{
		Window* pWindow = (*pIter);	
		if( pWindow->windowID == a_iWindowID )
		{	
			glfwSetWindowPos( pWindow->windowHandle, (int)a_fPos[0], (int)a_fPos[1] );
			break;
		}
	}
}

void Windows::SetWindowAlpha( int a_iWindowID, float a_fOpacity )
{
	std::vector<Window*>::iterator pIter = WindowList.begin();
	for( ; pIter != WindowList.end(); ++pIter)
	{
		Window* pWindow = (*pIter);	
		if( pWindow->windowID == a_iWindowID )
		{	
			glfwSetWindowTransparency( pWindow->windowHandle, a_fOpacity );
			break;
		}
	}
}

GLFWwindow* Windows::GetCurrentActiveWindow()
{
	return CurrentWindow->windowHandle;
}

void Windows::UpdateWindows()
{
	std::vector<Window*>::iterator pIter = WindowList.begin();
	for( ; pIter != WindowList.end(); ++pIter)
	{
		Window* pWindow = (*pIter);	
		int h, w;
		glfwGetWindowSize( pWindow->windowHandle, &w, &h );
		pWindow->pWindowSize = Vec2( (float)w, (float)h );
		pWindow->pProjection.Ortho( 0.f, pWindow->pWindowSize[0], 0.f, pWindow->pWindowSize[1], 0.f, 100.f );
		glfwSwapBuffers( pWindow->windowHandle );
		glfwRestoreWindow( pWindow->windowHandle );
	}
}

void Windows::SetWindowShape( int a_iWindowID, int a_iWindowShape )
{
	std::vector<Window*>::iterator pIter = WindowList.begin();
	for( ; pIter != WindowList.end(); ++pIter)
	{
		Window* pWindow = (*pIter);	
		if( pWindow->windowID == a_iWindowID )
		{				
			Window* pWindow = (*pIter);	

			switch( a_iWindowShape )
			{

			case STANDARD_WINDOW:
					windowPoints = new float*[4];
					windowPoints[0] = SquareWindow[0] * (*pWindow->pWindowSize);
					windowPoints[1] = SquareWindow[1] * (*pWindow->pWindowSize);
					windowPoints[2] = SquareWindow[2] * (*pWindow->pWindowSize);
					windowPoints[3] = SquareWindow[3] * (*pWindow->pWindowSize);

					glfwSetWindowRegion( pWindow->windowHandle, windowPoints, 4 );
				break;

			case TRIANGLE_WINDOW:
					windowPoints = new float*[3];
					windowPoints[0] = TriangleWindow[0] * (*pWindow->pWindowSize);
					windowPoints[1] = TriangleWindow[1] * (*pWindow->pWindowSize);
					windowPoints[2] = TriangleWindow[2] * (*pWindow->pWindowSize);

					glfwSetWindowRegion( pWindow->windowHandle, windowPoints, 3 );
				break;

			case Z_WINDOW:
					windowPoints = new float*[10];
					windowPoints[0] = Vec2( ZWindow[0] * (*pWindow->pWindowSize) );
					windowPoints[1] = ZWindow[1] * (*pWindow->pWindowSize);
					windowPoints[2] = ZWindow[2] * (*pWindow->pWindowSize);
					windowPoints[3] = ZWindow[3] * (*pWindow->pWindowSize);
					windowPoints[4] = ZWindow[4] * (*pWindow->pWindowSize);
					windowPoints[5] = ZWindow[5] * (*pWindow->pWindowSize);
					windowPoints[6] = ZWindow[6] * (*pWindow->pWindowSize);
					windowPoints[7] = ZWindow[7] * (*pWindow->pWindowSize);
					windowPoints[8] = ZWindow[8] * (*pWindow->pWindowSize);
					windowPoints[9] = ZWindow[9] * (*pWindow->pWindowSize);

					glfwSetWindowRegion( pWindow->windowHandle, windowPoints, 10 );
				break;

			default:
				// No compatible wnidow shape chosen
				// default is borderless box window
					windowPoints = new float*[4];
					windowPoints[0] = SquareWindow[0] * (*pWindow->pWindowSize);
					windowPoints[1] = SquareWindow[1] * (*pWindow->pWindowSize);
					windowPoints[2] = SquareWindow[2] * (*pWindow->pWindowSize);
					windowPoints[3] = SquareWindow[3] * (*pWindow->pWindowSize);

					glfwSetWindowRegion( pWindow->windowHandle, windowPoints, 4 );
				break;
			}
			break;
		}
		
	}
}

void Windows::SetWindowShape( int a_iWindowID, float* a_fWindowPoints )
{
	std::vector<Window*>::iterator pIter = WindowList.begin();
	for( ; pIter != WindowList.end(); ++pIter)
	{
		Window* pWindow = (*pIter);	
		if( pWindow->windowID == a_iWindowID )
		{				
			Window* pWindow = (*pIter);	

			// This is going to get messy really fast...
			// Sample size of the spectrum is 64
			// So we need that *2 points plus the bottom 2 corners.
			windowPoints = new float*[100];


			// Loop through the spectrum
			// All points will start at 0.5 and if they are less than 
			// that they will have 0.5 added to them. Maybe. Testing timeeeeee
			for( int i = 0; i < 100; ++i )
			{
				if( i == 0 ) // This is the first point
				{
					windowPoints[i] = Vec2( 0.f, 0.f ) * (*pWindow->pWindowSize);
				}
				else if( i == 99 ) // last point
				{					
					windowPoints[i] = Vec2( 1.f, 0.f ) * (*pWindow->pWindowSize);
				}
				else
				{
					windowPoints[i] = Vec2( ( 0.005f * (float)i ), a_fWindowPoints[i] ) * (*pWindow->pWindowSize); 
				}
				
				printf( "%f,%f\n", windowPoints[i][0], windowPoints[i][1] );
			}
			printf( "\n" );
			// First point will be top left corner (0.f, (1.f-a_fWindowPoints[0])
			//windowPoints[0] = Vec2( 0.f, a_fWindowPoints[0] );
			// 3rd last point is top right corner
			//windowPoints[127] = Vec2( 1.f, a_fWindowPoints[63] );
			// The last 2 points are the bottom corners
			
			
			
			glfwSetWindowRegion( pWindow->windowHandle, windowPoints, 100 ); 
			delete[] windowPoints;
			break;
		}
	}
}

ScreenQuadrant* Windows::GetCurrentQuadrant( float a_fX, float a_fY )
{
	if( a_fX < CurrentWindow->pWindowSize[0] / 2 )
	{
		// Left side
		if( a_fY < CurrentWindow->pWindowSize[1] / 2 )
		{
			// Top Side
			return &( CurrentWindow->m_pScreenQuadrants[0] );
		}
		else
		{
			// Bottom Side
			return &( CurrentWindow->m_pScreenQuadrants[2] );
		}
	}
	else
	{
		// Right side
		if( a_fY < CurrentWindow->pWindowSize[1] / 2 )
		{
			// Top Side
			return &( CurrentWindow->m_pScreenQuadrants[1] );
		}
		else
		{
			// Bottom Side
			return &( CurrentWindow->m_pScreenQuadrants[3] );
		}
	}
}