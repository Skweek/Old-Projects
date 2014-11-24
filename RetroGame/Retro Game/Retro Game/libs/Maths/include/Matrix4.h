///////////////////////////////////////
// File:			Matrix4.h
// Author:			Nick Smith
// Creation Date:	30th April 2013
// Notes:			Matrix4 class
///////////////////////////////////////

#ifndef _Matrix4_H_
#define	_Matrix4_H_

class Vec4;

#include "MathUtil.h"

class DECLDIR Matrix4
{
public:
	//+===================================+//
	//	Constructors
	//+===================================+//
	Matrix4();
	Matrix4( float a_fMatrixArray[4][4] );

	//+===================================+//
	//	Creates basic matrices
	//+===================================+//
	Matrix4 IdentityMatrix();
	Matrix4 OrthoView();
	Matrix4 ZeroMatrix();

	//+===================================+//
	//	rotate matrices by a point
	//+===================================+//
	Matrix4 RotateMatrixX( float a_fRotation );
	Matrix4 RotateMatrixY( float a_fRotation );
	Matrix4 RotateMatrixZ( float a_fRotation );
	
	//+===================================+//
	//	transform matrix by vector
	//+===================================+//
	Matrix4 Transform( Vec4 a_pVec4 );



	//+===================================+//
	//	Equals operator overload
	//+===================================+//
	void		operator=		( const Matrix4& a_Mat1 );
	bool		operator==		( const Matrix4& a_Mat1 );
	bool		operator!=		( const Matrix4& a_Mat1 );
	//+===================================+//
	//	Addition operator overload
	//+===================================+//
	Matrix4		operator+		( const Matrix4& a_Mat1 );
	Matrix4		operator+=		( const Matrix4& a_Mat1 );
	//+===================================+//
	//	Subtraction operator overload
	//+===================================+//
	Matrix4		operator-		( const Matrix4& a_Mat1 );
	Matrix4		operator-=		( const Matrix4& a_Mat1 );
	//+===================================+//
	//	Multiply operator overload
	//+===================================+//
	Matrix4		operator*		( const Matrix4& a_Mat1 );
	Matrix4&	operator*=		( const Matrix4& a_Mat1 );
	Matrix4		operator*		( const float& a_Float	);
	Matrix4&	operator*=		( const float& a_Float	);
	Vec4		operator*		( const Vec4& a_Vec4	);

	union
	{
		float m_fMatrixStructure[4][4];
		struct
		{
			float m_11, m_12, m_13, m_14;
			float m_21, m_22, m_23, m_24;
			float m_31, m_32, m_33, m_34;
			float m_41, m_42, m_43, m_44;
		};
	};
};

#endif