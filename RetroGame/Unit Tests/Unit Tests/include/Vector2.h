#ifndef _VECTOR2_H_
#define _VECTOR2_H_

void Vector2()
{
	std::cout << "\t\t\t==~Vector 2~==" << std::endl;
	Vec2 pVec1;
	Vec2 pVec2;
	Vec2 pVecResults;
	float fResults;

	//+===========
	//Constructors
	std::cout << std::endl << "+============== Constructors ==================+" << std::endl;
	std::cout << "__Vec2()__" << std::endl << std::endl;
	std::cout << "\tVec2() should return (0, 0) " << std::endl;
	pVecResults = Vec2();
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << " )\n\n";


	std::cout << "__Vec2(float* a_fpV2)__" << std::endl << std::endl;
	std::cout << "\tVec2((float*)Vec2(3.5, 3.5)) should return (3.5, 3.5) " << std::endl;
	std::cout << "\tThis is converting a vector into a float pointer and then back\n\tto a vector. I don't know why, but it might be useful." << std::endl;
	pVec1 = Vec2(3.5f, 3.5f);
	pVecResults = Vec2(static_cast<float*>(pVec1));
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << " )\n\n";


	std::cout << "__Vec2( const float a_fX, const float a_fY )__" << std::endl << std::endl;
	std::cout << "\tVec2(2.5, 5.6) should return (2.5, 5.6) " << std::endl;
	pVecResults = Vec2(2.5f, 5.6f);
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << " )\n\n";

	//+=========
	//Overloads
	std::cout << std::endl << "+=============== Equal Overloads =================+" << std::endl;

	std::cout << "__Vec2 = Vec2__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f) = (5.3f, 2.5f) should make the first vector equal the value of the second vector" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVec2 = Vec2(5.3f, 2.5f);
	pVec1 = pVec2;
	std::cout << "\tActual output is: ( " << pVec1.m_fX << ", " << pVec1.m_fY << " )\n\n";

	std::cout << "__Vec2 == Vec2__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f) == (5.3f, 2.5f) should return false" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVec2 = Vec2(5.3f, 2.5f);
	if ( pVec1 == pVec2 )
	{
		std::cout << "\tVectors are the same\n\n";
	}
	else
	{
		std::cout << "\tVectors are not the same\n\n";
	}

	

	std::cout << std::endl << "+=============== Addition Overloads =================+" << std::endl;

	std::cout << "__Vec2 + Vec2__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f) + (5.3f, 2.5f) expected answer is (9.8, 8.0)" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVec2 = Vec2(5.3f, 2.5f);
	pVecResults = pVec1 + pVec2;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << " )\n\n";


	std::cout << "__Vec2 + float__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f) + 5.3f expected answer is (9.8, 10.8)" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVecResults = pVec1 + 5.3f;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << " )\n\n";


	std::cout << "__Vec2 += Vec2__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f) += (5.3f, 2.5f) expected answer is to override initial vector with (9.8, 8.0)" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVec2 = Vec2(5.3f, 2.5f);
	pVec1 += pVec2;
	std::cout << "\tActual output is: ( " << pVec1.m_fX << ", " << pVec1.m_fY << " )\n\n";


	std::cout << "__Vec2 += float__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f) += 5.3f expected answer is to override initial vector with (9.8, 10.8)" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVec1 += 5.3f;
	std::cout << "\tActual output is: ( " << pVec1.m_fX << ", " << pVec1.m_fY << " )\n\n";
	

	std::cout << std::endl << "+============== Subtraction Overloads ==================+" << std::endl;

		std::cout << "__Vec2 - Vec2__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f) - (5.3f, 2.5f) expected answer is (-0.8, 3.0)" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVec2 = Vec2(5.3f, 2.5f);
	pVecResults = pVec1 - pVec2;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << " )\n\n";


	std::cout << "__Vec2 - float__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f) - 5.3f expected answer is (-0.8, 0.2)" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVecResults = pVec1 - 5.3f;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << " )\n\n";


	std::cout << "__Vec2 -= Vec2__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f) -= (5.3f, 2.5f) expected answer is to override initial vector with (-0.8, 3.0)" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVec2 = Vec2(5.3f, 2.5f);
	pVec1 -= pVec2;
	std::cout << "\tActual output is: ( " << pVec1.m_fX << ", " << pVec1.m_fY << " )\n\n";


	std::cout << "__Vec2 -= float__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f) -= 5.3f expected answer is to override initial vector with (-0.8, 0.2)" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVec1 -= 5.3f;
	std::cout << "\tActual output is: ( " << pVec1.m_fX << ", " << pVec1.m_fY << " )\n\n";
	

	std::cout << std::endl << "+================ Division Overloads ================+" << std::endl;

	std::cout << "__Vec2 / Vec2__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f) / (5.3f, 2.5f) expected answer is (0.849, 2.2)" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVec2 = Vec2(5.3f, 2.5f);
	pVecResults = pVec1 / pVec2;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << " )\n\n";


	std::cout << "__Vec2 / float__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f) / 5.3f expected answer is (0.849, 1.03)" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVecResults = pVec1 / 5.3f;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << " )\n\n";


	std::cout << "__Vec2 /= Vec2__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f) /= (5.3f, 2.5f) expected answer is to override initial vector with (0.849, 2.2)" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVec2 = Vec2(5.3f, 2.5f);
	pVec1 /= pVec2;
	std::cout << "\tActual output is: ( " << pVec1.m_fX << ", " << pVec1.m_fY << " )\n\n";


	std::cout << "__Vec2 /= float__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f) /= 5.3f expected answer is to override initial vector with (0.849, 1.03)" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVec1 /= 5.3f;
	std::cout << "\tActual output is: ( " << pVec1.m_fX << ", " << pVec1.m_fY << " )\n\n";

	std::cout << std::endl << "+================ Multiplication Overloads ================+" << std::endl;

	std::cout << "__Vec2 * Vec2__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f) * (5.3f, 2.5f) expected answer is (23.85, 13.75)" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVec2 = Vec2(5.3f, 2.5f);
	pVecResults = pVec1 * pVec2;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << " )\n\n";


	std::cout << "__Vec2 * float__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f) * 5.3f expected answer is (23.85, 29.15)" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVecResults = pVec1 * 5.3f;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << " )\n\n";


	std::cout << "__Vec2 *= Vec2__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f) *= (5.3f, 2.5f) expected answer is to override initial vector with (23.85, 13.75)" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVec2 = Vec2(5.3f, 2.5f);
	pVec1 *= pVec2;
	std::cout << "\tActual output is: ( " << pVec1.m_fX << ", " << pVec1.m_fY << " )\n\n";


	std::cout << "__Vec2 *= float__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f) *= 5.3f expected answer is to override initial vector with (23.85, 29.15)" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVec1 *= 5.3f;
	std::cout << "\tActual output is: ( " << pVec1.m_fX << ", " << pVec1.m_fY << " )\n\n";

	//+=========
	//Other Functions
	std::cout << std::endl << "+=============== Get magnitude =================+" << std::endl;

	std::cout << "__GetMagnitude()__" << std::endl << std::endl;
	std::cout << "\tVec2(4.5f, 5.5f).GetMagnitude()) expected answer is (7.106)" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVec2 = Vec2(5.3f, 2.5f);
	fResults = pVec1.GetMagnitude();
	std::cout << "\tActual output is: ( " << fResults << " )\n\n";

	std::cout << std::endl << "+=============== Normalise Vector =================+" << std::endl;

	std::cout << "__NormaliseVec2()__" << std::endl << std::endl;
	std::cout << "\tVec2(4.5f, 5.5f).NormaliseVec2()) expected answer is (0.633, 0.733)" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVec2 = Vec2(5.3f, 2.5f);
	pVecResults = pVec1.NormaliseVec2();
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << " )\n\n";

	std::cout << std::endl << "+=============== Linear Interpolation =================+" << std::endl;

	std::cout << "__LinearInterpolation( const Vec2& a_pVec1, float a_fDest )__" << std::endl << std::endl;
	std::cout << "\tVec2(4.5f, 5.5f).LinearInterpolation(Vec2(5.3f, 2.5f), 5.f) expected answer is (-15.5, -14.5)" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVec2 = Vec2(5.3f, 2.5f);
	pVecResults = pVec1.LinearInterpolation(pVec2, 5);
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << " )\n\n";

	std::cout << std::endl << "+=============== Dot Product =================+" << std::endl;

	std::cout << "__DotProduct( const Vec2& a_pVec1 )__" << std::endl << std::endl;
	std::cout << "\tVec2(4.5f, 5.5f).DotProduct(Vec2(5.3f, 2.5f)) expected answer is (37.6)" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVec2 = Vec2(5.3f, 2.5f);
	fResults = pVec1.DotProduct(pVec2);
	std::cout << "\tActual output is: ( " << fResults << " )\n\n";

	std::cout << std::endl << "+=============== Rotate by Point =================+" << std::endl;

	std::cout << "__RotateVec2( const Vec2& a_pVec1, float a_fRotationInDegrees )__" << std::endl << std::endl;
	std::cout << "\tVec2(4.5f, 5.5f).LinearInterpolation(Vec2(5.3f, 2.5f), 5.f) expected answer is (4.76, 5.55)" << std::endl;
	pVec1 = Vec2(4.5f, 5.5f);
	pVec2 = Vec2(5.3f, 2.5f);
	pVecResults = pVec1.RotateVec2(pVec2, 5);
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << " )\n\n";

	std::cout << std::endl << "+=============== Get Angle =================+" << std::endl;

	std::cout << "__GetAngle( const Vec2& a_pVec1 )__" << std::endl << std::endl;
	std::cout << "\tVec2(5.f, 5.f).DotProduct(Vec2(0.f, 5.f)) expected answer is (90)" << std::endl;
	pVec1 = Vec2(5.f, 5.f);
	pVec2 = Vec2(5.f, -5.f);
	fResults = pVec1.GetAngle(pVec2);
	std::cout << "\tActual output is: ( " << fResults << " )\n\n";
}

#endif //_VECTOR2_H_