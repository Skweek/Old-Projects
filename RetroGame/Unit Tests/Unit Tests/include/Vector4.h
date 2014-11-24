#ifndef _VECTOR4_H_
#define _VECTOR4_H_

void Vector4()
{
	std::cout << "\t\t\t==~Vector 2~==" << std::endl;
	Vec4 pVec1;
	Vec4 pVec2;
	Vec4 pVecResults;
	float fResults;

	//+===========
	//Constructors
	std::cout << std::endl << "+============== Constructors ==================+" << std::endl;
	std::cout << "__Vec4()__" << std::endl << std::endl;
	std::cout << "\tVec4() should return (0, 0, 0, 0) " << std::endl;
	pVecResults = Vec4();
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << ", " << pVecResults.m_fW << " )\n\n";

	std::cout << "__Vec4( float a_fX, float a_fY, float a_fZ )__" << std::endl << std::endl;
	std::cout << "\tVec4(2.5, 5.6, 4.3, 1) should return (2.5, 5.6, 4.3, 1) " << std::endl;
	pVecResults = Vec4(2.5f, 5.6f, 4.3f, 1.f);
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << ", " << pVecResults.m_fW << " )\n\n";

	//+=========
	//Overloads
	std::cout << std::endl << "+=============== Equal Overloads =================+" << std::endl;

	std::cout << "__Vec4 = Vec4__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f, 1) = (5.3f, 2.5f, 4.3f, 1) should make the first vector equal the value of the second vector" << std::endl;
	pVec1 = Vec4(4.5f, 5.5f, 4.3f, 1);
	pVec2 = Vec4(5.3f, 2.5f, 4.3f, 1);
	pVec1 = pVec2;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << ", " << pVecResults.m_fW << " )\n\n";

	std::cout << "__Vec4 == Vec4__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f, 1) == (5.3f, 2.5f, 4.3f, 1) should return false" << std::endl;
	pVec1 = Vec4(4.5f, 5.5f, 4.3f, 1);
	pVec2 = Vec4(5.3f, 2.5f, 4.3f, 1);
	if ( pVec1 == pVec2 )
	{
		std::cout << "\tVectors are the same\n\n";
	}
	else
	{
		std::cout << "\tVectors are not the same\n\n";
	}

	

	std::cout << std::endl << "+=============== Addition Overloads =================+" << std::endl;

	std::cout << "__Vec4 + Vec4__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f, 1) + (5.3f, 2.5f, 4.3f, 1) expected answer is (9.8, 8.0, 8.0, 8.6)" << std::endl;
	pVec1 = Vec4(4.5f, 5.5f, 4.3f, 1);
	pVec2 = Vec4(5.3f, 2.5f, 4.3f, 1);
	pVecResults = pVec1 + pVec2;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << ", " << pVecResults.m_fW << " )\n\n";


	std::cout << "__Vec4 += Vec4__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f, 1) += (5.3f, 2.5f, 4.3f, 1) expected answer is to override initial vector with (9.8, 10.8, 10.8)" << std::endl;
	pVec1 = Vec4(4.5f, 5.5f, 4.3f, 1);
	pVec2 = Vec4(5.3f, 2.5f, 4.3f, 1);
	pVec1 += pVec2;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << ", " << pVecResults.m_fW << " )\n\n";

	std::cout << std::endl << "+============== Subtraction Overloads ==================+" << std::endl;

		std::cout << "__Vec4 - Vec4__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f, 1) - (5.3f, 2.5f, 4.3f, 1) expected answer is (-0.8, 3.0, 3.0)" << std::endl;
	pVec1 = Vec4(4.5f, 5.5f, 4.3f, 1);
	pVec2 = Vec4(5.3f, 2.5f, 4.3f, 1);
	pVecResults = pVec1 - pVec2;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << ", " << pVecResults.m_fW << " )\n\n";


	std::cout << "__Vec4 -= Vec4__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f, 1) -= (5.3f, 2.5f, 4.3f) expected answer is to override initial vector with (-0.8, 0.2, 0.2)" << std::endl;
	pVec1 = Vec4(4.5f, 5.5f, 4.3f, 1);
	pVec2 = Vec4(5.3f, 2.5f, 4.3f, 1);
	pVec1 -= pVec2;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << ", " << pVecResults.m_fW << " )\n\n";

	std::cout << std::endl << "+================ Division Overloads ================+" << std::endl;

	std::cout << "__Vec4 / Vec4__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f, 1) / (5.3f, 2.5f, 4.3f, 1) expected answer is (0.849, 2.2, 2.2)" << std::endl;
	pVec1 = Vec4(4.5f, 5.5f, 4.3f, 1);
	pVec2 = Vec4(5.3f, 2.5f, 4.3f, 1);
	pVecResults = pVec1 / pVec2;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << ", " << pVecResults.m_fW << " )\n\n";


	std::cout << "__Vec4 / float__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f, 1) / 5.3f expected answer is (0.849, 1.03, 1.03)" << std::endl;
	pVec1 = Vec4(4.5f, 5.5f, 4.3f, 1);
	pVecResults = pVec1 / 5.3f;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << ", " << pVecResults.m_fW << " )\n\n";


	std::cout << "__Vec4 /= Vec4__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f, 1) /= (5.3f, 2.5f, 4.3f, 1) expected answer is to override initial vector with (0.849, 1.03, 1.03)" << std::endl;
	pVec1 = Vec4(4.5f, 5.5f, 4.3f, 1);
	pVec2 = Vec4(5.3f, 2.5f, 4.3f, 1);
	pVec1 /= pVec2;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << ", " << pVecResults.m_fW << " )\n\n";


	std::cout << "__Vec4 /= float__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f, 1) /= 5.3f expected answer is to override initial vector with (0.849, 1.03, 1.03)" << std::endl;
	pVec1 = Vec4(4.5f, 5.5f, 4.3f, 1);
	pVec1 /= 5.3f;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << ", " << pVecResults.m_fW << " )\n\n";

	std::cout << std::endl << "+================ Multiplication Overloads ================+" << std::endl;

	std::cout << "__Vec4 * Vec4__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f, 1) * (5.3f, 2.5f, 4.3f, 1) expected answer is (23.85, 13.75, 13.75)" << std::endl;
	pVec1 = Vec4(4.5f, 5.5f, 4.3f, 1);
	pVec2 = Vec4(5.3f, 2.5f, 4.3f, 1);
	pVecResults = pVec1 * pVec2;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << ", " << pVecResults.m_fW << " )\n\n";


	std::cout << "__Vec4 * float__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f, 1) * 5.3f expected answer is (23.80, 29.15, 29.15)" << std::endl;
	pVec1 = Vec4(4.5f, 5.5f, 4.3f, 1);
	pVecResults = pVec1 * 5.3f;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << ", " << pVecResults.m_fW << " )\n\n";


	std::cout << "__Vec4 *= Vec4__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f, 1) *= (5.3f, 2.5f, 4.3f, 1) expected answer is to override initial vector with (23.80, 29.15, 29.15)" << std::endl;
	pVec1 = Vec4(4.5f, 5.5f, 4.3f, 1);
	pVec2 = Vec4(5.3f, 2.5f, 4.3f, 1);
	pVec1 *= pVec2;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << ", " << pVecResults.m_fW << " )\n\n";


	std::cout << "__Vec4 *= float__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f, 1) *= 5.3f expected answer is to override initial vector with (23.80, 29.15, 29.15)" << std::endl;
	pVec1 = Vec4(4.5f, 5.5f, 4.3f, 1);
	pVec1 *= 5.3f;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << ", " << pVecResults.m_fW << " )\n\n";

	//+=========
	//Other Functions
	std::cout << std::endl << "+=============== Get magnitude =================+" << std::endl;

	std::cout << "__GetMagnitude()__" << std::endl << std::endl;
	std::cout << "\tVec4(4.5f, 5.5f, 4.3f, 1).GetMagnitude()) expected answer is (8.306)" << std::endl;
	pVec1 = Vec4(4.5f, 5.5f, 4.3f, 1);
	fResults = pVec1.GetMagnitude();
	std::cout << "\tActual output is: ( " << fResults << " )\n\n";

	std::cout << std::endl << "+=============== Normalise Vector =================+" << std::endl;

	std::cout << "__NormaliseVec4()__" << std::endl << std::endl;
	std::cout << "\tVec4(4.5f, 5.5f, 4.3f, 1).NormaliseVec4()) expected answer is (0.541, 0.662, 0.662)" << std::endl;
	pVec1 = Vec4(4.5f, 5.5f, 4.3f, 1);
	pVecResults = pVec1.NormaliseVec4();
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << ", " << pVecResults.m_fW << " )\n\n";

	std::cout << std::endl << "+=============== Dot Product =================+" << std::endl;

	std::cout << "__DotProduct( const Vec4& a_pVec1 )__" << std::endl << std::endl;
	std::cout << "\tVec4(4.5f, 5.5f, 4.3f, 1).DotProduct(Vec4(5.3f, 2.5f, 4.3f, 1)) expected answer is (56.09)" << std::endl;
	pVec1 = Vec4(4.5f, 5.5f, 4.3f, 1);
	pVec2 = Vec4(5.3f, 2.5f, 4.3f, 1);
	fResults = pVec1.DotProduct(pVec2);
	std::cout << "\tActual output is: ( " << fResults << " )\n\n";

	std::cout << std::endl << "+=============== Get Angle =================+" << std::endl;

	std::cout << "__GetAngle( const Vec4& a_pVec1 )__" << std::endl << std::endl;
	std::cout << "\tVec4(5.f, 5.f, 4.3f, 1).DotProduct(Vec4(0.f, 5.f, 4.3f, 1)) expected answer is (90)" << std::endl;
	pVec1 = Vec4(5.f, 5.f, 4.3f, 1);
	pVec2 = Vec4(5.f, -5.f, 4.3f, 1);
	fResults = pVec1.GetAngle(pVec2);
	std::cout << "\tActual output is: ( " << fResults << " )\n\n";
}

#endif //_VECTOR4_H_