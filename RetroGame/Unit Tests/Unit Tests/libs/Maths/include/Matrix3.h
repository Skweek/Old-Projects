///////////////////////////////////////
// File:			Matrix3.h
// Author:			Nick Smith
// Creation Date:	29th April 2013
// Notes:			Matrix3 class
///////////////////////////////////////

#ifndef _MATRIX3_H_
#define	_MATRIX3_H_

class Vec3;

#include "MathUtil.h"

class DECLDIR Matrix3
{
public:
	//+===================================+//
	//	Constructors
	//+===================================+//
	Matrix3();
	Matrix3( float a_fMatrixArray[3][3] );

	//+===================================+//
	//  Convert to float pointer	
	//+===================================+//
	operator		float*	()						{ return static_cast<float*>(m_fMatrixStruct_s);					}
	operator const	float*	() const				{ return static_cast<const float*>(m_fMatrixStruct_s);				}

	//+===================================+//
	//	Creates basic matrices
	//+===================================+//
	Matrix3 IdentityMatrix();
	Matrix3 OrthoView();
	Matrix3 ZeroMatrix();

	//+===================================+//
	//	rotate matrices by a point
	//+===================================+//
	Matrix3 RotateMatrixX( float a_fRotation );
	Matrix3 RotateMatrixY( float a_fRotation );
	Matrix3 RotateMatrixZ( float a_fRotation );

	Matrix3 RotateMatrix( Vec3& a_Vec3 );
	
	//+===================================+//
	//	transform matrix by vector
	//+===================================+//
	Vec3 TransformPoint( Vec3 a_pVec3 );
	Vec3 RotatePoint( Vec3 a_pVec3 );





	//+===================================+//
	//	Equals operator overload
	//+===================================+//
	void		operator=		( const Matrix3& a_Mat1 );
	bool		operator==		( const Matrix3& a_Mat1 );
	bool		operator!=		( const Matrix3& a_Mat1 );
	//+===================================+//
	//	Addition operator overload
	//+===================================+//
	Matrix3		operator+		( const Matrix3& a_Mat1 );
	Matrix3		operator+		( const Vec3& a_Vec3	);
	Matrix3		operator+=		( const Matrix3& a_Mat1 );
	Matrix3		operator+=		( const Vec3& a_Vec3	);
	//+===================================+//
	//	Subtraction operator overload
	//+===================================+//
	Matrix3		operator-		( const Matrix3& a_Mat1 );
	Matrix3		operator-		( const Vec3& a_Vec3	);
	Matrix3		operator-=		( const Matrix3& a_Mat1 );
	Matrix3		operator-=		( const Vec3& a_Vec3	);
	//+===================================+//
	//	Multiply operator overload
	//+===================================+//
	Matrix3		operator*		( const Matrix3& a_Mat1 );
	Matrix3&	operator*=		( const Matrix3& a_Mat1 );
	Matrix3		operator*		( const float& a_Float	);
	Matrix3&	operator*=		( const float& a_Float	);
	Vec3		operator*		( const Vec3& a_Vec3	);


	union
	{
		struct
		{
			float m_fMatrixStructure[3][3];
		};

		struct
		{
			float m_fMatrixStruct_s[9];
		};

		struct
		{
			float m_11, m_12, m_13;
			float m_21, m_22, m_23;
			float m_31, m_32, m_33;
		};
	};
};


#endif