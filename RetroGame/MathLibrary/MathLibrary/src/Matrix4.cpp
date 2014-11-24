#include "Matrix4.h"

#include "Vec3.h"
#include "Vec4.h"

// Define a shorthand term for the matrix variable (neatens things up a bit)
#define mat m_fMatrixStructure

Matrix4::Matrix4()
{
	for ( int i = 0; i < 4; ++i )
	{
		for ( int j = 0; j < 4; ++j )
		{
			mat[i][j] = 0.f; 
		}
	}	
}

Matrix4::Matrix4( float a_fMatrixArray[4][4] )
{
	for ( int i = 0; i < 4; ++i )
	{
		for ( int j = 0; j < 4; ++j )
		{
			mat[i][j] = a_fMatrixArray[i][j]; 
		}
	}	
}

Matrix4::Matrix4(	const float& a_f11,  const float& a_f12,  const float& a_f13,  const float& a_f14,  
					const float& a_f21,  const float& a_f22,  const float& a_f23,  const float& a_f24,  
					const float& a_f31,  const float& a_f32,  const float& a_f33,  const float& a_f34,  
					const float& a_f41,  const float& a_f42,  const float& a_f43,  const float& a_f44  )
{
	m_11 = a_f11;	m_12 = a_f12;	m_13 = a_f13;	m_14 = a_f14;	
	m_21 = a_f21;	m_22 = a_f22;	m_23 = a_f23;	m_24 = a_f24;	
	m_31 = a_f31;	m_32 = a_f32;	m_33 = a_f33;	m_34 = a_f34;	
	m_41 = a_f41;	m_42 = a_f42;	m_43 = a_f43;	m_44 = a_f44;	
}
																																																																																																																																			#pragma region Operator Overloads

//+===================================+//
//	Equals operator overload
//+===================================+//
void Matrix4::operator= ( const Matrix4& a_Mat1 )
{
	for ( int i = 0; i < 4; ++i )
	{
		for ( int j = 0; j < 4; ++j )
		{
			mat[i][j] = a_Mat1.mat[i][j]; 
		}
	}	
}
bool Matrix4::operator==	( const Matrix4& a_Mat1 )
{
	for ( int i = 0; i < 4; ++i )
	{
		for ( int j = 0; j < 4; ++j )
		{
			if ( mat[i][j] != a_Mat1.mat[i][j] )
			{
				return false;
			}
		}
	}	

	return true;
}

bool Matrix4::operator!=	( const Matrix4& a_Mat1 )
{
	for ( int i = 0; i < 4; ++i )
	{
		for ( int j = 0; j < 4; ++j )
		{
			if ( mat[i][j] != a_Mat1.mat[i][j] )
			{
				return true;
			}
		}
	}	

	return false;
}
//+===================================+//
//	Addition operator overload
//+===================================+//
Matrix4 Matrix4::operator+ ( const Matrix4& a_Mat1 )
{
	float a_fMatrixArray[4][4] = 
	{
		mat[0][0] + a_Mat1.mat[0][0], mat[0][1] + a_Mat1.mat[0][1], mat[0][2] + a_Mat1.mat[0][2], mat[0][3] + a_Mat1.mat[0][3],
		mat[1][0] + a_Mat1.mat[1][0], mat[1][1] + a_Mat1.mat[1][1], mat[1][2] + a_Mat1.mat[1][2], mat[1][3] + a_Mat1.mat[1][3],
		mat[2][0] + a_Mat1.mat[2][0], mat[2][1] + a_Mat1.mat[2][1], mat[2][2] + a_Mat1.mat[2][2], mat[2][3] + a_Mat1.mat[2][3],
		mat[3][0] + a_Mat1.mat[3][0], mat[3][1] + a_Mat1.mat[3][1], mat[3][2] + a_Mat1.mat[3][2], mat[3][3] + a_Mat1.mat[3][3],
	};

	return Matrix4( a_fMatrixArray );
}

Matrix4 Matrix4::operator+ ( const Vec3& a_Vec3 )
{
	float a_fMatrixArray[4][4] = 
	{
		mat[0][0], mat[0][1], mat[0][2], mat[0][3],
		mat[1][0], mat[1][1], mat[1][2], mat[1][3],
		mat[2][0], mat[2][1], mat[2][2], mat[2][3],
		mat[3][0] + a_Vec3.m_fX, mat[3][1] + a_Vec3.m_fY, mat[3][2] + a_Vec3.m_fZ, mat[3][3]
	};

	return Matrix4( a_fMatrixArray );
}

Matrix4 Matrix4::operator+=	( const Matrix4& a_Mat1 )
{
	*this = *this + a_Mat1;
	return *this;
}

Matrix4 Matrix4::operator+= ( const Vec3& a_vec3 )
{
	*this = *this + a_vec3;
	return *this;
}
//+===================================+//
//	Subtraction operator overload
//+===================================+//
Matrix4 Matrix4::operator- ( const Matrix4& a_Mat1 )
{
	float a_fMatrixArray[4][4] = 
	{
		mat[0][0] - a_Mat1.mat[0][0], mat[0][1] - a_Mat1.mat[0][1], mat[0][2] - a_Mat1.mat[0][2], mat[0][3] - a_Mat1.mat[0][3],
		mat[1][0] - a_Mat1.mat[1][0], mat[1][1] - a_Mat1.mat[1][1], mat[1][2] - a_Mat1.mat[1][2], mat[1][3] - a_Mat1.mat[1][3],
		mat[2][0] - a_Mat1.mat[2][0], mat[2][1] - a_Mat1.mat[2][1], mat[2][2] - a_Mat1.mat[2][2], mat[2][3] - a_Mat1.mat[2][3],
		mat[3][0] - a_Mat1.mat[3][0], mat[3][1] - a_Mat1.mat[3][1], mat[3][2] - a_Mat1.mat[3][2], mat[3][3] - a_Mat1.mat[3][3],
	};

	return Matrix4( a_fMatrixArray );
}

Matrix4 Matrix4::operator- ( const Vec3& a_Vec3 )
{
	float a_fMatrixArray[4][4] = 
	{
		mat[0][0], mat[0][1], mat[0][2], mat[0][3],
		mat[1][0], mat[1][1], mat[1][2], mat[1][3],
		mat[2][0], mat[2][1], mat[2][2], mat[2][3],
		mat[3][0] - a_Vec3.m_fX, mat[3][1] - a_Vec3.m_fY, mat[3][2] - a_Vec3.m_fZ, mat[3][3]
	};

	return Matrix4( a_fMatrixArray );
}

Matrix4 Matrix4::operator-=	( const Matrix4& a_Mat1 )
{
	*this = *this - a_Mat1;
	return *this;
}

Matrix4 Matrix4::operator-= ( const Vec3& a_vec3 )
{
	*this = *this - a_vec3;
	return *this;
}
//+===================================+//
//	Multiply operator overload
//+===================================+//
Matrix4 Matrix4::operator* ( const Matrix4& a_Mat1 )
{
	float a_fMatrixArray[4][4] = 
	{
		( mat[0][0] * a_Mat1.mat[0][0] ) + ( mat[0][1] * a_Mat1.mat[1][0] ) + ( mat[0][2] * a_Mat1.mat[2][0] ) + ( mat[0][3] * a_Mat1.mat[3][0] ), // 0, 0
		( mat[0][0] * a_Mat1.mat[0][1] ) + ( mat[0][1] * a_Mat1.mat[1][1] ) + ( mat[0][2] * a_Mat1.mat[2][1] ) + ( mat[0][3] * a_Mat1.mat[3][1] ), // 1, 0
		( mat[0][0] * a_Mat1.mat[0][2] ) + ( mat[0][1] * a_Mat1.mat[1][2] ) + ( mat[0][2] * a_Mat1.mat[2][2] ) + ( mat[0][3] * a_Mat1.mat[3][2] ), // 2, 0
		( mat[0][0] * a_Mat1.mat[0][3] ) + ( mat[0][1] * a_Mat1.mat[1][3] ) + ( mat[0][2] * a_Mat1.mat[2][3] ) + ( mat[0][3] * a_Mat1.mat[3][3] ), // 3, 0
											 							  																	  
		( mat[1][0] * a_Mat1.mat[0][0] ) + ( mat[1][1] * a_Mat1.mat[1][0] ) + ( mat[1][2] * a_Mat1.mat[2][0] ) + ( mat[1][3] * a_Mat1.mat[3][0] ), // 0, 1
		( mat[1][0] * a_Mat1.mat[0][1] ) + ( mat[1][1] * a_Mat1.mat[1][1] ) + ( mat[1][2] * a_Mat1.mat[2][1] ) + ( mat[1][3] * a_Mat1.mat[3][1] ), // 1, 1
		( mat[1][0] * a_Mat1.mat[0][2] ) + ( mat[1][1] * a_Mat1.mat[1][2] ) + ( mat[1][2] * a_Mat1.mat[2][2] ) + ( mat[1][3] * a_Mat1.mat[3][2] ), // 2, 1
		( mat[1][0] * a_Mat1.mat[0][3] ) + ( mat[1][1] * a_Mat1.mat[1][3] ) + ( mat[1][2] * a_Mat1.mat[2][3] ) + ( mat[1][3] * a_Mat1.mat[3][3] ), // 3, 1
											 							  																	  
		( mat[2][0] * a_Mat1.mat[0][0] ) + ( mat[2][1] * a_Mat1.mat[1][0] ) + ( mat[2][2] * a_Mat1.mat[2][0] ) + ( mat[2][3] * a_Mat1.mat[3][0] ), // 0, 2
		( mat[2][0] * a_Mat1.mat[0][1] ) + ( mat[2][1] * a_Mat1.mat[1][1] ) + ( mat[2][2] * a_Mat1.mat[2][1] ) + ( mat[2][3] * a_Mat1.mat[3][1] ), // 1, 2
		( mat[2][0] * a_Mat1.mat[0][2] ) + ( mat[2][1] * a_Mat1.mat[1][2] ) + ( mat[2][2] * a_Mat1.mat[2][2] ) + ( mat[2][3] * a_Mat1.mat[3][2] ), // 2, 2
		( mat[2][0] * a_Mat1.mat[0][3] ) + ( mat[2][1] * a_Mat1.mat[1][3] ) + ( mat[2][2] * a_Mat1.mat[2][3] ) + ( mat[2][3] * a_Mat1.mat[3][3] ), // 3, 2
																																			  
		( mat[3][0] * a_Mat1.mat[0][0] ) + ( mat[3][1] * a_Mat1.mat[1][0] ) + ( mat[3][2] * a_Mat1.mat[2][0] ) + ( mat[3][3] * a_Mat1.mat[3][0] ), // 0, 3
		( mat[3][0] * a_Mat1.mat[0][1] ) + ( mat[3][1] * a_Mat1.mat[1][1] ) + ( mat[3][2] * a_Mat1.mat[2][1] ) + ( mat[3][3] * a_Mat1.mat[3][1] ), // 1, 3
		( mat[3][0] * a_Mat1.mat[0][2] ) + ( mat[3][1] * a_Mat1.mat[1][2] ) + ( mat[3][2] * a_Mat1.mat[2][2] ) + ( mat[3][3] * a_Mat1.mat[3][2] ), // 2, 3
		( mat[3][0] * a_Mat1.mat[0][3] ) + ( mat[3][1] * a_Mat1.mat[1][3] ) + ( mat[3][2] * a_Mat1.mat[2][3] ) + ( mat[3][3] * a_Mat1.mat[3][3] ), // 3, 3
	};

	return Matrix4( a_fMatrixArray );
}

Matrix4 Matrix4::operator* ( const float& a_Float )
{
	float a_fMatrixArray[4][4] = 
	{
		( mat[0][0] * a_Float ), // 0, 0
		( mat[1][0] * a_Float ), // 1, 0
		( mat[2][0] * a_Float ), // 2, 0
		( mat[3][0] * a_Float ), // 3, 0
											 							  
		( mat[0][1] * a_Float ), // 0, 1
		( mat[1][1] * a_Float ), // 1, 1
		( mat[2][1] * a_Float ), // 2, 1
		( mat[3][1] * a_Float ), // 3, 1
											 							  
		( mat[0][2] * a_Float ), // 0, 2
		( mat[1][2] * a_Float ), // 1, 2
		( mat[2][2] * a_Float ), // 2, 2
		( mat[3][2] * a_Float ), // 3, 2

		( mat[0][3] * a_Float ), // 0, 3
		( mat[1][3] * a_Float ), // 1, 3
		( mat[2][3] * a_Float ), // 2, 3
		( mat[3][3] * a_Float ), // 3, 3
	};

	return Matrix4( a_fMatrixArray );
}

Vec4 Matrix4::operator* ( const Vec4& a_Vec4 )
{
	Vec4 a_fNewVec4 = 
	Vec4(
		( mat[0][0] * a_Vec4.m_fX ) + ( mat[0][1] * a_Vec4.m_fY ) + ( mat[0][2] * a_Vec4.m_fZ ) + ( mat[0][3] * a_Vec4.m_fZ ),
		( mat[1][0] * a_Vec4.m_fX ) + ( mat[1][1] * a_Vec4.m_fY ) + ( mat[1][2] * a_Vec4.m_fZ ) + ( mat[1][3] * a_Vec4.m_fZ ),
		( mat[2][0] * a_Vec4.m_fX ) + ( mat[2][1] * a_Vec4.m_fY ) + ( mat[2][2] * a_Vec4.m_fZ ) + ( mat[2][3] * a_Vec4.m_fZ ), 
		( mat[3][0] * a_Vec4.m_fX ) + ( mat[3][1] * a_Vec4.m_fY ) + ( mat[3][2] * a_Vec4.m_fZ ) + ( mat[3][3] * a_Vec4.m_fZ )
	);

	return a_fNewVec4;
}

Matrix4& Matrix4::operator*=	( const Matrix4& a_Mat1 )
{
	*this = *this * a_Mat1;
	return *this;
		
}

Matrix4& Matrix4::operator*=	( const float& a_Float )
{
	*this = *this * a_Float;
	return *this;
		
}


//+===================================+//
//	Creates basic matrices
//+===================================+//
const Matrix4 Matrix4::IdentityMatrix = Matrix4(	1.f, 0.f, 0.f, 0.f, 
													0.f, 1.f, 0.f, 0.f, 
													0.f, 0.f, 1.f, 0.f, 
													0.f, 0.f, 0.f, 1.f );

const Matrix4 Matrix4::OrthoView = Matrix4(			1.f, 0.f, 0.f, 0.f, 
													0.f, 1.f, 0.f, 0.f, 
													0.f, 0.f, 1.f, 0.f, 
													0.f, 0.f, 0.f, 1.f );

const Matrix4 Matrix4::ZeroMatrix = Matrix4(		1.f, 0.f, 0.f, 0.f, 
													0.f, 1.f, 0.f, 0.f, 
													0.f, 0.f, 1.f, 0.f, 
													0.f, 0.f, 0.f, 1.f );

//+===================================+//
//	rotate matrices by a point
//+===================================+//
void Matrix4::RotateMatrixX( float a_fRotation )
{
	m_11 = 1.f;						m_12 = -0.f;					m_13 =  0.f;	m_14 = 0.f;
	m_21 = 0.f;						m_22 = cosf( a_fRotation );		m_23 =  -sinf( a_fRotation );	m_24 = 0.f;
	m_31 = 0.f;						m_32 = sinf( a_fRotation );		m_33 =  cosf( a_fRotation );	m_34 = 0.f;
	m_41 = 0.f;						m_42 = 0.f;						m_43 =  0.f;	m_44 = 1.f;
}

void Matrix4::RotateMatrixY( float a_fRotation )
{
	m_11 = cosf( a_fRotation );		m_12 = -sinf( a_fRotation );	m_13 =  0.f;	m_14 = 0.f;
	m_21 = 0.f;						m_22 = 	0.f;					m_23 =  0.f;	m_24 = 0.f;
	m_31 = -sinf( a_fRotation );	m_32 = cosf( a_fRotation );		m_33 =  1.f;	m_34 = 0.f;
	m_41 = 0.f;						m_42 = 0.f;						m_43 =  0.f;	m_44 = 1.f;
}

void Matrix4::RotateMatrixZ( float a_fRotation )
{
	m_11 = cosf( a_fRotation );		m_12 = -sinf( a_fRotation );	m_13 =  0.f;	m_14 = 0.f;
	m_21 = sinf( a_fRotation );		m_22 = cosf( a_fRotation );		m_23 =  0.f;	m_24 = 0.f;
	m_31 = 0.f;						m_32 = 0.f;						m_33 =  1.f;	m_34 = 0.f;
	m_41 = 0.f;						m_42 = 0.f;						m_43 =  0.f;	m_44 = 1.f;
}

//+===================================+//
//	Transform matrix by vector
//+===================================+//
Vec3 Matrix4::TransformPoint( Vec3 a_pVec3 )
{
	Matrix4 temp = Matrix4( *this + a_pVec3 );
	return ( Vec3( temp.m_31, temp.m_32, temp.m_33) );
}