#include "UIElements.h"

#include "FontManager.h" // Need this for drawing text
#include "Window.h"

// Base UI Element
UIElement::UIElement( Vec2 a_pPos, Vec2 a_pSize, int a_iID )
{
	m_pPos = a_pPos;
	m_pSize = a_pSize;

	m_iID = a_iID;
}

UIElement::~UIElement()
{

}

// Button Element
UIButton::UIButton( Vec2 a_pPos, Vec2 a_pSize, int a_iID, const char* a_ccImageUp, const char* a_ccImageDown ) : UIElement( a_pPos, a_pSize, a_iID )
{
	m_uiImageDown = LoadTexture( a_ccImageDown );
	m_uiImageUp = LoadTexture( a_ccImageUp );
	
	m_iButtonState = UI_BUTTON_UP;

	m_pClickable = Vec4( a_pPos.m_fX, a_pPos.m_fY, a_pPos.m_fX + a_pSize.m_fX, a_pPos.m_fY + a_pSize.m_fY );

	ClickFunction = 0;
	m_bPressed = false;
}

UIButton::~UIButton()
{

}

void UIButton::SetClickFunction( std::function<void()> function )
{
	ClickFunction = function;
}

void UIButton::Draw( GLuint m_uiShader )
{
	Matrix4 mat = Matrix4( m_pSize[0], 0.f, 0.f, 0.f, 
							 0.f, m_pSize[1], 0.f, 0.f, 
							  0.f, 0.f, 1.f, 0.f, 
							  m_pPos[0], m_pPos[1], 0.f, 1.f );

	GLuint ModelID = glGetUniformLocation( m_uiShader, "Model" );
	glUniformMatrix4fv( ModelID, 1, false, mat );	

	glActiveTexture( GL_TEXTURE0 );
	if( m_iButtonState == UI_BUTTON_DOWN )
	{
		glBindTexture( GL_TEXTURE_2D, m_uiImageDown );	
	}
	else
	{
		glBindTexture( GL_TEXTURE_2D, m_uiImageUp );	
	}

	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

}

void UIButton::Update()
{
	// We need to actually see if the mouse button has been pressed
	// For now only check left mouse button, implement default mouse button
	// check later maybe
	if( glfwGetMouseButton( Windows::Get()->GetCurrentActiveWindow(), GLFW_MOUSE_BUTTON_1 ) == 1 )
	{
		// Alright now get the mouse position to pass through to the button update function
		static double x, y;
		glfwGetCursorPos(Windows::Get()->GetCurrentActiveWindow(), &x, &y );

		// For now only check to see if it is clicked
		// Fancy stuff when this works
		if( OnClick( Vec2( (float)x, (float)y ) ) )
		{
			m_iButtonState = UI_BUTTON_DOWN;
			m_bPressed = true;
		}
		else
		{
			m_iButtonState = UI_BUTTON_UP;
		}
	}
	else if( m_bPressed )
	{
		m_iButtonState = UI_BUTTON_DOWN;

		m_bPressed = false;

		if( ClickFunction != 0 )
		{				
			ClickFunction();
		}
		
	}
	else
	{
		m_iButtonState = UI_BUTTON_UP;
	}
}

bool UIButton::OnClick( Vec2 a_pMousePos )
{
	float x = a_pMousePos.m_fX;
	float y = a_pMousePos.m_fY;
	if( x < m_pClickable[2] && x > m_pClickable[0] &&
		y < m_pClickable[3] && y > m_pClickable[1] )
	{
		return true; // yup, it was clicked
	}

	return false; // nope, wasn't clicked
}

// Label Element
UILabel::UILabel( Vec2 a_pPos, int a_iID, std::string a_ccText, Vec4 a_pTextColour ) : UIElement( a_pPos, Vec2(), a_iID )
{
	
	this->m_ccText = a_ccText;
	m_pTextColour = a_pTextColour;
	m_pVarPointer = nullptr;
}

UILabel::~UILabel()
{

}

void UILabel::SetText( const char* a_ccText )
{
	this->m_ccText = a_ccText;
}

void UILabel::SetTextColour( Vec4 a_pColour )
{
	m_pTextColour = a_pColour;
}

void UILabel::SetVariablePointer( int a_iType, void* p )
{
	m_pVarPointer = p;
	m_iVarType = a_iType;
}

void UILabel::Draw( GLuint m_uiShader )
{
	FontManager::Get()->DrawString( m_ccText.c_str(), Vec3( m_pPos[0], m_pPos[1], 0.f ), m_pTextColour );



	m_uiShader;
	// Deal with label backgrounds later, possibly
	// with fancy effects
}

void UILabel::Update()
{
	// Update text if it is linked to a variable
	if( m_pVarPointer != nullptr )
	{
		char buff[256];
		
		switch( m_iVarType )
		{
		case TYPE_CHAR:			
			sprintf( buff, "%s", *(std::string*)m_pVarPointer );
			break;

		case TYPE_FLOAT:
			sprintf( buff, "%f", *(float*)m_pVarPointer );
			break;

		case TYPE_INT:			
			sprintf( buff, "%i", *(int*)m_pVarPointer );
			break;
		}

		m_ccText = buff;
	}
}


// Meter Element
UIMeter::UIMeter( Vec2 a_pPos, Vec2 a_pSize, int a_iID, const char* a_ccMeterImageFile, 
				const char* a_ccBGImageFile, float* a_fMeterPadding ) : UIElement( a_pPos, a_pSize, a_iID )
{
	m_pMeterPos = Vec2( a_pSize[0] - ( a_pSize[0] - a_fMeterPadding[0] ), 
						a_pSize[1] - ( a_pSize[1] - a_fMeterPadding[1] ) ) + a_pPos;
	m_pMeterSize = Vec2( a_pSize[0]  - ( 2 * a_fMeterPadding[0] ), 
						 a_pSize[1]  - ( 2 * a_fMeterPadding[1] ) );

	m_uiBGImage = LoadTexture( a_ccBGImageFile );
	m_uiMeterImage = LoadTexture( a_ccMeterImageFile );

	MeterFunction = 0;
	m_fMeterVariable = nullptr;

	m_fMinValue = 0;
	m_fMaxValue = 100;
	m_fCurValue = 100;
}

UIMeter::~UIMeter()
{

}

void UIMeter::SetMeterFunction( void ( *p )() )
{
	MeterFunction = p;
}

void UIMeter::SetMeterVariable( void* p )
{
	m_fMeterVariable = p;
}

void UIMeter::Draw( GLuint m_uiShader )
{
	// Draw each image on top of each other until
	// I can figure the stupid FBO out
	Matrix4 mat = Matrix4( m_pSize[0], 0.f, 0.f, 0.f, 
							 0.f, m_pSize[1], 0.f, 0.f, 
							  0.f, 0.f, 1.f, 0.f, 
							  m_pPos[0], m_pPos[1], 0.f, 1.f );

	GLuint ModelID = glGetUniformLocation( m_uiShader, "Model" );
	glUniformMatrix4fv( ModelID, 1, false, mat );	

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, m_uiBGImage );	

	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

	mat = Matrix4( m_pMeterSize[0], 0.f, 0.f, 0.f, 
							 0.f, m_pMeterSize[1], 0.f, 0.f, 
							  0.f, 0.f, 1.f, 0.f, 
							  m_pMeterPos[0], m_pMeterPos[1], 0.f, 1.f );
	glUniformMatrix4fv( ModelID, 1, false, mat );	

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, m_uiMeterImage );	

	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
}

void UIMeter::Update()
{
	// Set the current value
	if( m_fMeterVariable != nullptr )
	{
		m_fCurValue = *(float*)m_fMeterVariable;		
	}
	
	if( m_fCurValue > m_fMaxValue )
		{
			m_fCurValue = m_fMaxValue;
		}

	// If current value is less than min value then call meter function
	if( m_fCurValue <= m_fMinValue )
	{
		if( MeterFunction != 0 )
		{
			MeterFunction();
		}
	}

	// Update the meter length - TO-DO: Vertical meters
	static float fMeterStep = m_pMeterSize[0] / 100.f;
	
	m_pMeterSize[0] = m_fCurValue * fMeterStep;
}

void UIMeter::SetValue( float a_fValue )
{
	m_fCurValue = a_fValue;
}

float UIMeter::GetValue()
{
	return m_fCurValue;
}
	
void UIMeter::SetMin( float a_fMin )
{
	m_fMinValue = a_fMin;
}

void UIMeter::SetMax( float a_fMax )
{
	m_fMaxValue = a_fMax;
}