#include "Startup.h"
#include "Window.h"
#include "FontManager.h"
#include "UILayouts.h"
#include "MapManager.h"
#include "Collision.h"
#include "Shapes.h"
#include "Sound.h"
#include "Scripts.h"
#include "ActorManager.h"

Startup* Startup::m_pInstance = nullptr;
bool bDebugInfo;

Startup::Startup()
{

}

Startup::~Startup()
{
	FontManager::Delete();
	UILayouts::Delete();
	MapManager::Delete();
	Shapes::Delete();
	DeInitActorManager();
	Windows::Delete();
	DeInitScripts();
	glfwTerminate();
}

Startup* Startup::Create()
{
	m_pInstance = new Startup;
	
	return m_pInstance;
}

Startup* Startup::Get()
{
	if( m_pInstance == nullptr )
	{
		m_pInstance = new Startup;
	}

	return m_pInstance;
}

void Startup::Delete()
{
	delete m_pInstance;
}

void Startup::ReloadEngine()
{	
	FontManager::Delete();
	UILayouts::Delete();
	MapManager::Delete();
	Shapes::Delete();
	Windows::Delete();
	DeInitScripts();

	m_pInstance = new Startup;
	InitialiseLibraries( 0, 0 );
}

int Startup::InitialiseLibraries( int a_iScreenHeight, int a_iScreenWidth )
{	
	bDebugInfo = false;

	m_dDeltaTime = 0;
	m_dGameTime = 0;
	m_dFrameTime = 0;

	// Initialise GLFW
	if( glfwInit() != GL_TRUE )
	{
		return LIBRARIES_FAILED_TO_LOAD;
	}

	// Init Scripts needs to be called first so we can access the 
	// Game information
	InitScripts();

	Windows::Create();
	Windows::Get()->CreateNewWindow( Vec2( (float)a_iScreenWidth, (float)a_iScreenHeight ), Vec2( 50, 50 ), 0 );

	FontManager::Create();
	UILayouts::Create();
	MapManager::Create();
	Shapes::Create();
	InitSound();
	InitActorManager();

	// Debug info
	if( bDebugInfo )
	{		
		printf( "Debug is turned on. \n" );

		std::cout << "OpenGL Version: " << glGetString( GL_VERSION ) << std::endl;
		std::cout << "Graphics card: " << glGetString( GL_VENDOR ) << " " << glGetString( GL_RENDERER ) << std::endl;
		GLFWmonitor* mon = glfwGetPrimaryMonitor();
		const GLFWvidmode* vid = glfwGetVideoMode( mon );
		std::cout << "Monitor Resolution: " << vid->width << " x " << vid->height << std::endl;
		std::cout << "Monitor RGB bits per pixel: " << vid->redBits << " bpp, " << vid->greenBits << " bpp, " << vid->blueBits << " bpp." << std::endl;
	}	
	return NO_ERROR;
}

void Startup::ClearScreen(int a_iWindowID, float a_fR, float a_fG, float a_fB, float a_fA )
{
	Windows::Get()->SetWindowFocus( a_iWindowID );
	glClearColor( a_fR, a_fG, a_fB, a_fA );
	glClear( GL_COLOR_BUFFER_BIT );
}

bool Startup::Update()
{
	if( Windows::Get()->WindowShouldClose() == 1 )
	{
		return false;
	}

	if( glfwGetKey( Windows::Get()->GetCurrentActiveWindow(), GLFW_KEY_F10 ) == 1 )
	{
		ReloadActors();
	}

	UpdateDeltaTime();
	
	// Update stuff
	UILayouts::Get()->Update();
	UpdateSounds();

	// Draw Stuff
	MapManager::Get()->DrawCurrentMap( 0 );
	MapManager::Get()->DrawCurrentMap( 1 );
	MapManager::Get()->DrawCurrentMap( 2 );
	//FontManager::Get()->Draw(); // Need to add text strings to a queue and render them at the same time
	UILayouts::Get()->Render();
	Shapes::Get()->Render();
	RenderAllActors();

	Windows::Get()->UpdateWindows();	

	glfwPollEvents();

	return true;
}

void Startup::UpdateDeltaTime()
{
	static double dCurTime = 0;
	static double dLastTime = 0;
	

	dCurTime = glfwGetTime();

	m_dDeltaTime = dCurTime - dLastTime;
	dLastTime = dCurTime;

	m_dGameTime += m_dDeltaTime;
	m_dFrameTime += m_dDeltaTime;

	// Update FPS
	if( m_dFrameTime > 1.f )
	{
		m_fFPS = 1.f / (float)m_dDeltaTime;
		m_dFrameTime -= 1.f;
	}
}