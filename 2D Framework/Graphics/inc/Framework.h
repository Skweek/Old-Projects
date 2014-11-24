////////////////////////////////////////////////////////////
// File: Framework.h
// Author: Nick Smith
// Date Created: 27th May 2013
// Brief: Framework entry point
////////////////////////////////////////////////////////////

#ifndef _FRAMEWORK_ENTRY_
#define _FRAMEWORK_ENTRY_

#ifndef DECLDIR
#define DECLDIR __declspec( dllexport )
#endif 

#include <functional>
#include <vector>

/** @defgroup Setup Framework Setup
 *
 *  Framework setup and handling
 *
 *  @{
 */

/**
 * @brief Initialises the engine framework
 *
 * Initialises the framework and opens a starting window of
 * a specified size
 *
 * @param a_iScreenHeight Height of the initial window
 * @param a_iScreenWidth Width of the initial window
 */
DECLDIR void StartFramework( int a_iScreenHeight, int a_iScreenWidth );

/**
 * @brief Creates a new window
 *
 * Creates a new window
 *
 * @param a_iScreenHeight Height of the window
 * @param a_iScreenWidth Width of the window
 * @param a_iScreenX Starting X position of the window
 * @param a_iScreenY Starting Y position of the window
 * @param a_iWindowID ID number for the window
 */
DECLDIR int NewWindow( int a_iScreenHeight, int a_iScreenWidth, int a_iScreenX, int a_iScreenY, int a_iWindowID );

/**
 * @brief Creates a new window
 *
 * Creates a new window
 *
 * @param a_fSize Float array for the window size
 * @param a_fPos Float array the the window start position
 * @param a_iWindowID ID number for the window
 */
DECLDIR int NewWindow( float* a_fSize, float* a_fPos, int a_iWindowID );

/**
 * @brief Sets the focus to a window
 *
 * Sets the specified window as the focused one
 * so it can be drawn to and accessed
 *
 * @param a_iWindowID ID number for the window to be focused
 */
DECLDIR void SetActiveWindow( int a_iWindowID );

/**
 * @brief Destroys a window
 *
 * Closes the specified window and deletes all associated
 * handles
 *
 * @param a_iWindowID ID number for the window to be deleted
 */
DECLDIR void DestroyWindow( int a_iWindowID );

/**
 * @brief Clears the screen
 *
 * Clears the current buffer and sets the default colour
 *
 * @param a_iWindowID ID number for the window
 * @param a_fR Red colour value
 * @param a_fG Green colour value
 * @param a_fB Blue colour value
 * @param a_fA Alpha value
 */
DECLDIR void RefreshScreen( int a_iWindowID, float a_fR, float a_fG, float a_fB, float a_fA );

/**
 * @brief Sets the specified windows title
 *
 * Sets the title of the specified window 
 *
 * @param a_iWindowID ID number for the window to be deleted
 * @param a_ccTitle String of characters to set as the window title
 */
DECLDIR void SetWindowTitle( int a_iWindowID, const char* a_ccTitle );

/**
 * @brief Sets the specified windows display region
 *
 * Sets the specified region to no resize mode and
 * changes the physical shape of the displayed window
 *
 * @param a_iWindowID ID number for the window to be deleted
 * @param a_iWindowShape Number specifying the shape to be selected
 */

DECLDIR void SetWindowShape( int a_iWindowID, float* a_fWindowPoints );
/**
 * @brief Sets the specified windows display region
 *
 * Sets the specified region to no resize mode and
 * changes the physical shape of the displayed window
 * This is a function specific to setting window to 
 * the shape of an audio wave form, needs to be
 * generalised.
 *
 * @param a_iWindowID ID number for the window to be deleted
 * @param a_fWindowPoints Points of the window
 */
DECLDIR void SetWindowShape( int a_iWindowID, int a_iWindowShape );

/**
 * @brief Sets windows position
 *
 * Sets specified windows origin point
 *
 * @param a_iWindowID ID number for the window to be deleted
 * @param a_fPos Float array of the position for the window
 */
DECLDIR void SetWindowPosition( int a_iWindowID, float* a_fPos );

/**
 * @brief Sets windows opacity
 *
 * Sets the opacity for the selected window and all of its 
 * components
 *
 * @param a_iWindowID ID number for the window to be deleted
 * @param a_fOpacity Value between 0-255 for the opacity
 */
DECLDIR void SetWindowAlpha( int a_iWindowID, float a_fOpacity );

/**
 * @brief Gets the time since the last frame update
 *
 * Returns the time since the last frame update
 */
DECLDIR double GetDeltaTime();

/**
 * @brief Gets the current FPS
 *
 * Returns the current frames rendered every second
 */
DECLDIR float GetFPS();

/**
 * @brief Updates the framework
 *
 * Called once every frame, this updates the entire scene
 * and draws everything again
 */
DECLDIR bool FrameworkUpdate();

/**
 * @brief Shuts down the framework
 *
 * Ends the framework and deletes any handles associated with it
 */
DECLDIR void FrameworkClose();
/** @} */ // end of Framework Setup

/** @defgroup Input Input Handling
 *  Handles input
 *  @{
 */
/**
 * @brief Updates key presses
 * 
 * Returns an int array of all the valid keys and
 * their current condition. 0 for unpressed and 1
 * for pressed.
 */
DECLDIR int* CheckInput();

/**
 * @brief Updates mouse position
 * 
 * Returns a float array containing the position 
 * of the mouse cursor.
 */
DECLDIR float* GetMousePos();
/** @} */ // end of Input

/** @defgroup Font Font Handling
 *  Handles font rendering
 *  @{
 */

/**
 * @brief Loads a font
 * 
 * Loads a font file and the ID as an integer.
 * 
 * @param a_ccFontFile Path to the font file
 */
DECLDIR int LoadFont( const char* a_ccFontFile );

/**
 * @brief Draws a string of text
 * 
 * Draws a string of text 
 * 
 * @param a_ccText String of characters to draw
 * @param a_fPos Float array for the position of the upper left corner of the string
 * @param a_fColour Float array of the colour to draw the string
 */
DECLDIR void DrawString( const char* a_ccText, float* a_fPos, float* a_fColour );

/**
 * @brief Sets the current font
 * 
 * Sets the font to be used for drawing.
 * 
 * @param a_iID Font ID to switch to
 */
DECLDIR void SetFont( int a_iID );

/**
 * @brief Get font ID
 * 
 * Returns the current fonts ID.
 */
DECLDIR int GetFont();

/** @} */ // end of Font

/** @defgroup Sprites Sprite Handling
 *  Handles sprite drawing and updating
 *  @{
 */

/**
 * @brief Creates a new actor
 * 
 * Creates a new actor and returns an int as the ID of the actor
 * 
 * @param a_ccActorFile The path to the file to load the actor information from
 * @param a_fPos The initial position of the actor
 */
DECLDIR int CreateNewActor( const char* a_ccActorFile, float* a_fPos );

/**
 * @brief Moves an actor
 * 
 * Moves the specified actor to the specified position
 * 
 * @param a_iID The id of the actor to be moved
 * @param a_fPos The initial position of the actor
 */
DECLDIR void MoveActor( int a_iID, float* a_fPos );

/**
 * @brief Draws an actor
 * 
 * Draws the specified actor
 * 
 * @param a_iID The id of the actor to be drawn
 */
DECLDIR void DrawActor( int a_iID );

/**
 * @brief Makes an actor face a specific direction
 * 
 * Turns an actor towards a direction.
 * 
 * @param a_iID The id of the actor to be drawn
 * @param a_iDirection The id of the actor to be drawn
 */
DECLDIR void TurnActor( int a_iID, int a_iDirection );

/** @} */ // end of Sprites

/** @defgroup Shapes Shape Drawing
 *  Handles the drawing of primitive shapes
 *  @{
 */
/**
 * @brief Draws a line
 * 
 * Draws a line between 2 points
 * 
 * @param a_fP1 Float array of the starting point
 * @param a_fP2 Float array of the end point
 * @param a_fColour Float array of colour to draw the line
 */
DECLDIR void DrawLine( float* a_fP1, float* a_fP2, float* a_fColour );


/** @} */ // end of Shapes

/** @defgroup Layouts Layout Handling
 *  Handles the loading, updating and drawing of layouts
 *  @{
 */

/**
 * @brief Loads a layout file
 * 
 * Loads a layout file and returns the ID as an integer.
 * 
 * @param a_ccLayoutFile Path to the layout file
 */
DECLDIR int LoadLayout( const char* a_ccLayoutFile );


/**
 * @brief Sets a labels variable
 * 
 * Sets the specified layout label's variable to get a value from.
 * The correct layout must first be selected using ::SetLayout
 * 
 * @param a_iID The labels ID 
 * @param a_iType The variables type 
 * @param p Pointer to a variable to be assigned
 */
DECLDIR void SetLabelVariable( int a_iID, int a_iType, void* p );

/**
 * @brief Sets a meters variable
 * 
 * Sets the specified layout meter's variable to get a value from.
 * The correct layout must first be selected using ::SetLayout
 * 
 * @param a_iID The meters ID 
 * @param p Pointer to a variable to be assigned
 */
DECLDIR void SetMeterVariable( int a_iID, void* p );

/**
 * @brief Sets a meters update event
 * 
 * Sets the specified layout meter's function to be called when
 * the meter value hits the minimum or maximum.
 * The correct layout must first be selected using ::SetLayout
 * 
 * @param a_iID The meters ID 
 * @param p Pointer to a function to be assigned
 */
DECLDIR void SetMeterFunction( int a_iID, void ( *p )() ); // Needs to fixed to work with std::function

/**
 * @brief Sets a meters min and max values
 * 
 * Sets the specified layout meter's minimum and maximum allowed values.
 * The correct layout must first be selected using ::SetLayout
 * 
 * @param a_iID The meters ID 
 * @param a_fValues Float array containing the min and max values
 */
DECLDIR void SetMeterMinMax( int a_iID, float* a_fValues );

/**
 * @brief Sets the current layout
 * 
 * Sets the layout to be used for drawing and for setting 
 * layout elements information.
 * 
 * @param a_iID The layout ID 
 */
DECLDIR void SetLayout( int a_iID );

/**
 * @brief Toggles drawing layouts
 * 
 * Toggles whether or not the layout should be drawn.
 * 
 * @param a_bToggle True/False 
 */
DECLDIR void ToggleLayoutDrawing( bool a_bToggle );


/** @} */ // end of Layouts

/** @defgroup Maps Map Handling
 *  Handles the loading, updating and drawing of maps
 *  @{
 */


/**
 * @brief Loads a map file
 * 
 * Loads a map file and returns the ID as an integer.
 * 
 * @param a_ccMapFile Path to the map file
 */
DECLDIR int LoadMap( const char* a_ccMapFile );

/**
 * @brief Loads an objects file
 * 
 * Loads an objects file and returns the result as a bool.
 * 
 * @param a_ccObjectsFile Path to the objects file
 */
DECLDIR bool LoadObjects( const char* a_ccObjectsFile );

/**
 * @brief Toggles drawing the map
 * 
 * Toggles whether or not the map should be drawn.
 * 
 * @param a_bToggle True/False 
 */
DECLDIR void ToggleMapDrawing( bool a_bToggle );

/**
 * @brief Sets the current map
 * 
 * Sets the map to be used for drawing and 
 * collision detection.
 * 
 * @param a_iID The map ID 
 */
DECLDIR void SetMap( int a_iID );

/** @} */ // end of Maps

/** @defgroup Collisions Collision Detection
 *  Handles the collision detection - Nothing here yet
 *  @{
 */

/** @} */ // end of Collisions

/** @defgroup Sounds Sound handling
 *  Handles the musics
 *  @{
 */

/**
 * @brief Loads a BGM sound file
 *
 * @param a_ccBGM Music file to be loaded, returns the sound ID
 */
DECLDIR int LoadBGMFile( const char* a_ccBGM );

/**
 * @brief Loads a SFX sound file
 *
 * @param a_ccSFX Music file to be loaded, returns the sound ID
 */
DECLDIR int LoadSFXFile( const char* a_ccSFX );

/**
 * @brief Plays the current BGM file
 */
DECLDIR void SetBGMPlaying( bool a_bPlaying );

/**
 * @brief Plays the current SFX file
 */
DECLDIR void SetSFXPlaying();

/**
 * @brief Sets the current BGM sound
 */
DECLDIR void SetCurrentBGM( int a_iID );

/**
 * @brief Sets the current SFX sound
 */
DECLDIR void SetCurrentSFX( int a_iID );

/**
 * @brief Gets the sound spectrum of the current BGM audio
 */
DECLDIR float* GetBGMSpectrum();

/** @} */ // end of Sounds


/** @defgroup Scripts Python Script handling
 *  Handles the scriptzzzz
 *  @{
 */

/**
 * @brief Reloads the main.py script
 *
 */
DECLDIR void ReloadScripts();

/**
 * @brief Finds a path between 2 points
 *
 * @param a_pStart The start point on the map
 * @param a_pEnd The end point on the map
 *
 */
DECLDIR float** FindPath( float* a_pStart, float* a_pEnd );

/**
 * @brief Finds the next step towards an object
 *
 * @param a_pStart The start point on the map
 * @param a_pEnd The end point on the map
 *
 */
DECLDIR float* FindNextPathNode( float* a_pStart, float* a_pEnd );

/**
 * @brief Finds the closest object froma  list of objects and gets the path to it
 *
 * @param a_pStart The start point on the map
 * @param a_pTargets Vector or target positions
 *
 */
DECLDIR float* FindClosestObject( float* a_pStart, std::vector<float*>a_pTargets );

/**
 * @brief Travels in the same direction as an object
 *
 * @param a_pTarget The targets velocity
 *
 */
DECLDIR float* AlignWithTarget( float* a_pTarget );

/**
 * @brief Moves towards a target object
 *
 * @param a_pTarget The targets position
 * @param a_pSelf The current objects position
 *
 */
DECLDIR float* FollowATarget( float* a_pTarget, float* a_pSelf );

/**
 * @brief Moves away from a target object
 *
 * @param a_pTarget The targets position
 * @param a_pSelf The current objects position
 *
 */
DECLDIR float* AvoidATarget( float* a_pTarget, float* a_pSelf );

/**
 * @brief Wanders around
 *
 * @param a_pSelf The targets position
 *
 */
DECLDIR float* WanderAround( float* a_pSelf );


/** @} */ // end of Scripts

/** @defgroup Keys Key Defines
 *  @{
 */

#pragma region key/mouse enum
#define MOUSE_BUTTON_1         0
#define MOUSE_BUTTON_2         1
#define MOUSE_BUTTON_3         2

/* Printable keys */
#define KEY_SPACE              32
#define KEY_APOSTROPHE         39  /* ' */
#define KEY_COMMA              44  /* , */
#define KEY_MINUS              45  /* - */
#define KEY_PERIOD             46  /* . */
#define KEY_SLASH              47  /* / */
#define KEY_0                  48
#define KEY_1                  49
#define KEY_2                  50
#define KEY_3                  51
#define KEY_4                  52
#define KEY_5                  53
#define KEY_6                  54
#define KEY_7                  55
#define KEY_8                  56
#define KEY_9                  57
#define KEY_SEMICOLON          59  /* ; */
#define KEY_EQUAL              61  /* = */
#define KEY_A                  65
#define KEY_B                  66
#define KEY_C                  67
#define KEY_D                  68
#define KEY_E                  69
#define KEY_F                  70
#define KEY_G                  71
#define KEY_H                  72
#define KEY_I                  73
#define KEY_J                  74
#define KEY_K                  75
#define KEY_L                  76
#define KEY_M                  77
#define KEY_N                  78
#define KEY_O                  79
#define KEY_P                  80
#define KEY_Q                  81
#define KEY_R                  82
#define KEY_S                  83
#define KEY_T                  84
#define KEY_U                  85
#define KEY_V                  86
#define KEY_W                  87
#define KEY_X                  88
#define KEY_Y                  89
#define KEY_Z                  90
#define KEY_LEFT_BRACKET       91  /* [ */
#define KEY_BACKSLASH          92  /* \ */
#define KEY_RIGHT_BRACKET      93  /* ] */
#define KEY_GRAVE_ACCENT       96  /* ` */
#define KEY_WORLD_1            161 /* non-US #1 */
#define KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define KEY_ESCAPE             256
#define KEY_ENTER              257
#define KEY_TAB                258
#define KEY_BACKSPACE          259
#define KEY_INSERT             260
#define KEY_DELETE             261
#define KEY_RIGHT              262
#define KEY_LEFT               263
#define KEY_DOWN               264
#define KEY_UP                 265
#define KEY_PAGE_UP            266
#define KEY_PAGE_DOWN          267
#define KEY_HOME               268
#define KEY_END                269
#define KEY_CAPS_LOCK          280
#define KEY_SCROLL_LOCK        281
#define KEY_NUM_LOCK           282
#define KEY_PRINT_SCREEN       283
#define KEY_PAUSE              284
#define KEY_F1                 290
#define KEY_F2                 291
#define KEY_F3                 292
#define KEY_F4                 293
#define KEY_F5                 294
#define KEY_F6                 295
#define KEY_F7                 296
#define KEY_F8                 297
#define KEY_F9                 298
#define KEY_F10                299
#define KEY_F11                300
#define KEY_F12                301
#define KEY_F13                302
#define KEY_F14                303
#define KEY_F15                304
#define KEY_F16                305
#define KEY_F17                306
#define KEY_F18                307
#define KEY_F19                308
#define KEY_F20                309
#define KEY_F21                310
#define KEY_F22                311
#define KEY_F23                312
#define KEY_F24                313
#define KEY_F25                314
#define KEY_KP_0               320
#define KEY_KP_1               321
#define KEY_KP_2               322
#define KEY_KP_3               323
#define KEY_KP_4               324
#define KEY_KP_5               325
#define KEY_KP_6               326
#define KEY_KP_7               327
#define KEY_KP_8               328
#define KEY_KP_9               329
#define KEY_KP_DECIMAL         330
#define KEY_KP_DIVIDE          331
#define KEY_KP_MULTIPLY        332
#define KEY_KP_SUBTRACT        333
#define KEY_KP_ADD             334
#define KEY_KP_ENTER           335
#define KEY_KP_EQUAL           336
#define KEY_LEFT_SHIFT         340
#define KEY_LEFT_CONTROL       341
#define KEY_LEFT_ALT           342
#define KEY_LEFT_SUPER         343
#define KEY_RIGHT_SHIFT        344
#define KEY_RIGHT_CONTROL      345
#define KEY_RIGHT_ALT          346
#define KEY_RIGHT_SUPER        347
#define KEY_MENU               348
#define KEY_LAST               KEY_MENU

enum KeyPress
{
	KEY_IS_UP,
	KEY_IS_DOWN
};

#pragma endregion

/** @} */ // end of Maps

/** @defgroup Enums Public Enums
*  @{
 */

enum WindowShapes
{
	STANDARD_WINDOW,
	TRIANGLE_WINDOW,
	CIRCLE_WINDOW,
	Z_WINDOW,

	// Window count
	WINDOW_COUNT
};

enum Collisions
{
	NO_COLL,
	COLL_LEFT,
	COLL_RIGHT,
	COLL_DOWN,
	COLL_UP, 
	COLL_SPRITE,

	COLL_COUNT
};

enum Attributes
{
	ATTRIB_BLOCK = COLL_COUNT,
	ATTRIB_DAMAGE,
	ATTRIB_HEAL,
	ATTRIB_REPEL,
	ATTRIB_NONE,

	ATTRIB_COUNT

};

/** @} */ // end of enums

#endif // _FRAMEWORK_ENTRY_