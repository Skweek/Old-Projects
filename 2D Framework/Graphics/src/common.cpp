////////////////////////////////////////////////////////////
// File: Common.cpp
// Author: Nick Smith
// Date Created: 9th June 2013
// Brief: Functions that don't need their own class but
//		  are used by multiple files
////////////////////////////////////////////////////////////


// All declarations are in "Utilities.h"
#include "Utilities.h"

// Window.h is needed to get current GL context
#include "Window.h"

// This is need by GLEW_MX apparently
GLEWContext* glewGetContext()
{
	GLEWContext* context = Windows::Get()->GetGLEWContext();
	if( context == NULL )
	{
		context = new GLEWContext();
		glewInit();
	}
	return context;
}

GLuint LoadTexture(const char* a_szTexture, unsigned int a_uiFormat /* = 
GL_RGBA */, unsigned int* a_uiWidth /* = nullptr */, unsigned int* a_uiHeight /* = 
nullptr */, unsigned int* a_uiBPP /* = nullptr*/)
{
	double time = glfwGetTime();
	FIBITMAP* pBitmap = nullptr;
	// check the file signature and deduce its format and load it
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(a_szTexture, 0);
	if(fif != FIF_UNKNOWN && FreeImage_FIFSupportsReading(fif)) 
	{
		pBitmap = FreeImage_Load(fif, a_szTexture);
	}
	if(pBitmap == nullptr) 
	{
		printf("Error: Failed to load image '%s'!\n", a_szTexture);
		return 0;
	}

	// optionally get the image width and height
	if(a_uiWidth != nullptr)
	*a_uiWidth = FreeImage_GetWidth(pBitmap);

	if(a_uiHeight != nullptr)
	*a_uiHeight = FreeImage_GetHeight(pBitmap);

	// force the image to RGBA
	unsigned int bpp = FreeImage_GetBPP(pBitmap);


	if( a_uiBPP != nullptr )
	*a_uiBPP = bpp/8;
	FREE_IMAGE_COLOR_TYPE fi_colourType = FreeImage_GetColorType(pBitmap);

	if(fi_colourType != FIC_RGBALPHA ) 
	{
		FIBITMAP* ndib = FreeImage_ConvertTo32Bits(pBitmap);
		FreeImage_Unload(pBitmap);
		pBitmap = ndib;
		bpp = FreeImage_GetBPP(pBitmap);
		fi_colourType = FreeImage_GetColorType(pBitmap);
	}

	// get the pixel data
	BYTE* pData = FreeImage_GetBits(pBitmap);

	// try to determine data type of file (bytes/floats)
	FREE_IMAGE_TYPE fit = FreeImage_GetImageType(pBitmap);
	GLenum eType = (fit == FIT_RGBF || fit == FIT_FLOAT) ? GL_FLOAT:GL_UNSIGNED_BYTE;

	// create GL texture
	GLuint textureID;
	glGenTextures( 1, &textureID );
	glBindTexture( GL_TEXTURE_2D, textureID );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, 
	FreeImage_GetWidth(pBitmap), 
	FreeImage_GetHeight(pBitmap), 0, 
	a_uiFormat, eType, pData);

	// specify default filtering and wrapping
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

	// unbind texture
	glBindTexture( GL_TEXTURE_2D, 0 );
	// delete data
	FreeImage_Unload(pBitmap);
	double elapsed = glfwGetTime() - time;
	std::cout << elapsed << std::endl;
	return textureID;
}


GLuint LoadShaders( const char* a_ccVertexFile, const char* a_ccFragmentFile )
	{
		// Create shaders
		GLuint VertexShader = glCreateShader( GL_VERTEX_SHADER );
			 
		GLuint FragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

		// Load GLSL code for Vertex shader
		std::string VertexShaderCode;
		std::ifstream VertexShaderStream;
		VertexShaderStream.open( a_ccVertexFile, std::ios::in );
		if( VertexShaderStream.is_open() )
		{
			std::string Line = "";
			while( getline( VertexShaderStream, Line ) )
				VertexShaderCode += "\n" + Line;
			VertexShaderStream.close();
		}
					 
		// Load GLSL code for Fragment Shader
		std::string FragmentShaderCode;
		std::ifstream FragmentShaderStream;
		FragmentShaderStream.open( a_ccFragmentFile, std::ios::in );
		if( FragmentShaderStream.is_open() )
		{
			std::string Line = "";
			while( getline( FragmentShaderStream, Line ) )
				FragmentShaderCode += "\n" + Line;
			FragmentShaderStream.close();
		}
			 
		//Used for making sure shaders compile correctly
		GLint iResult = GL_FALSE;

		// Compile the Vertex shader
		const char* VertexCode = VertexShaderCode.c_str();
		glShaderSource( VertexShader, 1, &VertexCode, NULL );
		glCompileShader( VertexShader );
			 
		// Check Vertex Shader
		glGetShaderiv( VertexShader, GL_COMPILE_STATUS, &iResult );
		if( iResult != GL_TRUE )
		{
			// Didn't compile, get the log and print it out
			char buffer[512];
			glGetShaderInfoLog( VertexShader, 512, NULL, buffer ); 
		}
			 
		// Compile the Fragment shader
		const char* FragmentCode = FragmentShaderCode.c_str();
		glShaderSource( FragmentShader, 1, &FragmentCode, NULL );
		glCompileShader( FragmentShader );
			 
		// Check Fragment Shader
		glGetShaderiv( FragmentShader, GL_COMPILE_STATUS, &iResult );
		if( iResult != GL_TRUE )
		{
			// Didn't compile, get the log and print it out
			char buffer[512];
			glGetShaderInfoLog( FragmentShader, 512, NULL, buffer ); 
		}
			 
		// Create and link the program
		GLuint ShaderProgram = glCreateProgram();
		glAttachShader( ShaderProgram, VertexShader );
		glAttachShader( ShaderProgram, FragmentShader );	
			 
		glLinkProgram( ShaderProgram );

		// Check the program for errors
		glGetProgramiv( ShaderProgram, GL_LINK_STATUS, &iResult );
		if( iResult != GL_TRUE )
		{
			// Didn't compile, get the log and print it out
			char buffer[512];
			glGetProgramInfoLog( ShaderProgram, 512, NULL, buffer ); 
		}
					 
		// Delete shaders (they are linked to program and not needed now)
		glDeleteShader( VertexShader );
		glDeleteShader( FragmentShader );
		
		// Return the program
		return ShaderProgram;
}

// Memory Management
std::vector<void*> MemoryList;
std::map<char*, int> MemoryLocations;

void LogMemory( void* p, char* file, int line )
{
	MemoryList.push_back( p );
	MemoryLocations.insert( std::pair<char*, int>( file, line ) );
	printf( "Added memory at %p from file %c line %i. \n", p, file, line );
}

void FreeMemory( void* p )
{
	free( p );
}

void CleanupMemory()
{

}