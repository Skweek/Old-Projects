#include "Startup.h"
#include "Window.h"
#include "FontManager.h"
#include "UILayouts.h"
#include "MapManager.h"
#include "Collision.h"
#include "Shapes.h"
#include "Sound.h"
#include "Scripts.h"
#include "AIBehaviours.h"
#include "ActorManager.h"

#include "Framework.h"

//+===================================+//
//	Screen Handling
//+===================================+//
void StartFramework( int a_iScreenHeight, int a_iScreenWidth )
{
	Startup::Create();
	Startup::Get()->InitialiseLibraries( a_iScreenHeight, a_iScreenWidth );
}

int NewWindow( int a_iScreenHeight, int a_iScreenWidth, int a_iScreenX, int a_iScreenY, int a_iWindowID )
{
	Windows::Get()->CreateNewWindow( Vec2( (float)a_iScreenHeight, (float)a_iScreenWidth ), Vec2( (float)a_iScreenX, (float)a_iScreenY ), a_iWindowID );

	return a_iWindowID;
}

int NewWindow( float* a_fSize, float* a_fPos, int a_iWindowID )
{
	Windows::Get()->CreateNewWindow( a_fSize, a_fPos, a_iWindowID );

	return a_iWindowID;
}

void SetActiveWindow( int a_iWindowID )
{
	Windows::Get()->SetWindowFocus( a_iWindowID );
}

void DestroyWindow( int a_iWindowID )
{
	Windows::Get()->DeleteWindow( a_iWindowID );
}

void RefreshScreen( int a_iWindowID, float a_fR, float a_fG, float a_fB, float a_fA )
{
	Startup::Get()->ClearScreen( a_iWindowID, a_fR, a_fG, a_fB, a_fA );
}

void SetWindowTitle( int a_iWindowID, const char* a_ccTitle )
{
	Windows::Get()->SetWindowTitle( a_iWindowID, a_ccTitle );
}

void SetWindowShape( int a_iWindowID, int a_iWindowShape )
{
	Windows::Get()->SetWindowShape( a_iWindowID, a_iWindowShape );
}

void SetWindowShape( int a_iWindowID, float* a_fWindowPoints )
{
	Windows::Get()->SetWindowShape( a_iWindowID, a_fWindowPoints );
}

void SetWindowPosition( int a_iWindowID, float* a_fPos )
{
	Windows::Get()->SetWindowPos( a_iWindowID, a_fPos );
}

void SetWindowAlpha( int a_iWindowID, float a_fOpacity )
{
	Windows::Get()->SetWindowAlpha( a_iWindowID, a_fOpacity );
}

double GetDeltaTime()
{
	return Startup::Get()->GetDeltaTime();
}

float GetFPS()
{
	return Startup::Get()->GetFPS();
}

bool FrameworkUpdate()
{
	// Update framework
	return Startup::Get()->Update();
}

void FrameworkClose()
{
	Startup::Delete();
}

//+===================================+//
//	Input Handling
//+===================================+//
int* CheckInput()
{
	static int InputList[KEY_LAST];

	for( int i = 0; i < KEY_LAST; ++i )
	{
		if( i < 8 )
		{
			InputList[i] = glfwGetMouseButton( Windows::Get()->GetCurrentActiveWindow(), i );
		}
		else 
		{
			InputList[i] = glfwGetKey( Windows::Get()->GetCurrentActiveWindow(), i );
		}
	}

	return InputList;
}

float* GetMousePos()
{
	double x, y;
	glfwGetCursorPos(Windows::Get()->GetCurrentActiveWindow(), &x, &y );
	return Vec2( (float)x, (float)y );
}

//+===================================+//
//	Font Rendering
//+===================================+//
int LoadFont( const char* a_ccFontFile )
{
	return FontManager::Get()->NewFont( a_ccFontFile );
}

void DrawString( const char* a_ccText, float* a_fPos, float* a_fColour )
{
	FontManager::Get()->DrawString( a_ccText, Vec3( a_fPos ), Vec4( a_fColour ) );
}

void SetFont( int a_iID )
{
	FontManager::Get()->SetFont( a_iID );
}

int GetFont()
{
	return FontManager::Get()->GetFont();
}

//+===================================+//
//	Sprites
//+===================================+//
int CreateNewActor( const char* a_ccActorFile, float* a_fPos )
{
	return NewActor( a_ccActorFile, Vec2( a_fPos ) );
}

void MoveActor( int a_iID, float* a_fPos )
{
	UpdateActor( a_iID, Vec2( a_fPos ) );
}

void DrawActor( int a_iID )
{
	AddActorToDrawQueue( a_iID );
}


void TurnActor( int a_iID, int a_iDirection )
{
	ActorFaceDirection( a_iID, a_iDirection );
}

//+===================================+//
//	Shapes
//+===================================+//
void DrawLine( float* a_p1, float* a_fp2, float* a_fColour )
{
	Shapes::Get()->DrawLine( Vec2( a_p1[0], a_p1[1] ), Vec2( a_fp2[0], a_fp2[1] ), 
							 Vec4( a_fColour[0], a_fColour[1], a_fColour[2], a_fColour[3] ) );
}

//+===================================+//
//	Layouts
//+===================================+//
int LoadLayout( const char* a_ccLayoutFile )
{
	return UILayouts::Get()->LoadLayout( a_ccLayoutFile );
}


void SetLabelVariable( int a_iID, int a_iType, void* p )
{
	UILayouts::Get()->SetLabelVariable( a_iID, a_iType, p );
}


void SetMeterVariable( int a_iID, void* p )
{
	UILayouts::Get()->SetMeterVariable( a_iID, p );
}

void SetMeterFunction( int a_iID, void ( *p )() )
{
	UILayouts::Get()->SetMeterFunction( a_iID, p );
}

void SetMeterMinMax( int a_iID, float* a_fValues )
{
	UILayouts::Get()->SetMeterMinMax( a_iID, Vec2( a_fValues[0], a_fValues[1] ) );
}

void SetLayout( int a_iID )
{
	UILayouts::Get()->SetLayout( a_iID );
}

void ToggleLayoutDrawing( bool a_bToggle )
{
	UILayouts::Get()->ToggleDrawLayout( a_bToggle );
}

//+===================================+//
//	Maps
//+===================================+//
int LoadMap( const char* a_ccMapFile )
{
	return MapManager::Get()->LoadMap( a_ccMapFile );
}

bool LoadObjects( const char* a_ccObjectsFile )
{
	return MapManager::Get()->LoadObjects( a_ccObjectsFile );
}

void ToggleMapDrawing( bool a_bToggle )
{
	MapManager::Get()->ToggleDrawMap( a_bToggle );
}

void SetMap( int a_iID )
{
	MapManager::Get()->SwapToMap( a_iID );
}

//+===================================+//
//	Collisions
//+===================================+//
// There isn't anything hereeeeeeeeeee

//+===================================+//
//	Sounds
//+===================================+//

int LoadBGMFile( const char* a_ccBGM )
{
	return LoadBGM( a_ccBGM );
}

int LoadSFXFile( const char* a_ccSFX )
{
	return LoadSFX( a_ccSFX );
}

void SetBGMPlaying( bool a_bPlaying )
{
	if( a_bPlaying )
	{
		PlayBGM();
	}
	else
	{
		PauseBGM();
	}
}

void SetSFXPlaying()
{
	PlaySFX();
}

void SetCurrentBGM( int a_iID )
{
	SetBGM( a_iID );
}

void SetCurrentSFX( int a_iID )
{
	SetSFX( a_iID );
}

float* GetBGMSpectrum()
{
	return BGMSpectrum();
}
//+===================================+//
//	Scripts
//+===================================+//
void ReloadScripts()
{
	ReloadScript();
}

float** FindPath( float* a_pStart, float* a_pEnd )
{
	std::vector<Vec2> pPath = GetPath( Vec2( a_pStart ), Vec2( a_pEnd ) );
	float** fPath = new float*[pPath.size()];
	for( int i = 0; i < (int)pPath.size(); ++i )
	{
		fPath[i] = new float[2];
	}
	
	int count = 0;
	
	while( count < (int)pPath.size() )
	{
		fPath[count][0] = pPath[count].m_fX;
		fPath[count][1] = pPath[count].m_fY;
		++count;
	}
	return fPath;
}

float* FindNextPathNode( float* a_pStart, float* a_pEnd )
{
	return FollowObject( Vec2( a_pStart ), Vec2( a_pEnd ) );
}

float* FindClosestObject( float* a_pStart, std::vector<float*>a_pTargets )
{
	std::vector<Vec2> pTargets;

	for( int target = 0; target < (int)a_pTargets.size(); ++target )
	{
		pTargets.push_back( Vec2( a_pTargets[target][0], a_pTargets[target][1] ) );
	}
	Vec2 pTarget = FindClosest( Vec2( a_pStart ), pTargets );

	return pTarget;
}

float* AlignWithTarget( float* a_pTarget )
{
	return AlignWith( Vec2( a_pTarget ) );
}

float* FollowATarget( float* a_pTarget, float* a_pSelf )
{
	return FollowObject( Vec2( a_pSelf ), Vec2( a_pTarget ) );
}

float* AvoidATarget( float* a_pTarget, float* a_pSelf )
{
	return FleeFromObject( Vec2( a_pSelf ), Vec2( a_pTarget ) );
}

float* WanderAround( float* a_pSelf )
{
	return Wander( Vec2( a_pSelf ) );
}