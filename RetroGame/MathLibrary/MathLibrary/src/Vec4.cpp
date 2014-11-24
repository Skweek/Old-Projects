#include <cmath>
#include "Vec4.h"
#include "Maths.h"

//+===================================+//
//	Constructors
//+===================================+//
Vec4::Vec4()
{
	m_fX = 0.f;
	m_fY = 0.f;
	m_fZ = 0.f;
	m_fW = 0.f;
}

Vec4::Vec4( float a_fX, float a_fY, float a_fZ, float a_fW )
{
	m_fX = a_fX;
	m_fY = a_fY;
	m_fZ = a_fZ;
	m_fW = a_fW;
}

Vec4::Vec4( unsigned int a_uiHex )
{
	m_fX = float( ( a_uiHex >> 24 ) & 0xFF );
	m_fY = float( ( a_uiHex >> 16 ) & 0xFF );
	m_fZ = float( ( a_uiHex >> 8 ) & 0xFF );
	m_fW = float( ( a_uiHex ) & 0xFF );
}

//+===================================+//
//	Get the magnitude of the Vec4
//  Returns result as a float	
//+===================================+//
float Vec4::GetMagnitude()
{
return sqrt( ( m_fX * m_fX ) + ( m_fY * m_fY ) + ( m_fZ * m_fZ ) + ( m_fW * m_fW ) );
}

//+===================================+//
//	Normalise the Vec4
//  returns result as a Vec4	
//+===================================+//
Vec4 Vec4::NormaliseVec4()
{
float fMag = GetMagnitude();
if ( fMag != 0 )
{		
	return Vec4( ( m_fX / fMag ), ( m_fY / fMag ), ( m_fZ / fMag ), ( m_fW / fMag )  );
}
return Vec4( 0.f, 0.f, 0.f, 0.f );
}

