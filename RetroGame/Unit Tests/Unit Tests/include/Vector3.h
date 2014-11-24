#ifndef _VECTOR3_H_
#define _VECTOR3_H_

void Vector3()
{
	std::cout << "\t\t\t==~Vector 2~==" << std::endl;
	Vec3 pVec1;
	Vec3 pVec2;
	Vec3 pVecResults;
	float fResults;

	//+===========
	//Constructors
	std::cout << std::endl << "+============== Constructors ==================+" << std::endl;
	std::cout << "__Vec3()__" << std::endl << std::endl;
	std::cout << "\tVec3() should return (0, 0) " << std::endl;
	pVecResults = Vec3();
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << " )\n\n";

	std::cout << "__Vec3( float a_fX, float a_fY, float a_fZ )__" << std::endl << std::endl;
	std::cout << "\tVec3(2.5, 5.6, 4.3) should return (2.5, 5.6, 4.3) " << std::endl;
	pVecResults = Vec3(2.5f, 5.6f, 4.3f);
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << " )\n\n";

	//+=========
	//Overloads
	std::cout << std::endl << "+=============== Equal Overloads =================+" << std::endl;

	std::cout << "__Vec3 = Vec3__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f) = (5.3f, 2.5f, 4.3f) should make the first vector equal the value of the second vector" << std::endl;
	pVec1 = Vec3(4.5f, 5.5f, 4.3f);
	pVec2 = Vec3(5.3f, 2.5f, 4.3f);
	pVec1 = pVec2;
	std::cout << "\tActual output is: ( " << pVec1.m_fX << ", " << pVec1.m_fY << ", " << pVec1.m_fZ << " )\n\n";

	std::cout << "__Vec3 == Vec3__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f) == (5.3f, 2.5f, 4.3f) should return false" << std::endl;
	pVec1 = Vec3(4.5f, 5.5f, 4.3f);
	pVec2 = Vec3(5.3f, 2.5f, 4.3f);
	if ( pVec1 == pVec2 )
	{
		std::cout << "\tVectors are the same\n\n";
	}
	else
	{
		std::cout << "\tVectors are not the same\n\n";
	}

	

	std::cout << std::endl << "+=============== Addition Overloads =================+" << std::endl;

	std::cout << "__Vec3 + Vec3__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f) + (5.3f, 2.5f, 4.3f) expected answer is (9.8, 8.0, 8.6)" << std::endl;
	pVec1 = Vec3(4.5f, 5.5f, 4.3f);
	pVec2 = Vec3(5.3f, 2.5f, 4.3f);
	pVecResults = pVec1 + pVec2;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << " )\n\n";


	std::cout << "__Vec3 + float__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f) + 5.3f expected answer is (9.8, 10.8, 9.6)" << std::endl;
	pVec1 = Vec3(4.5f, 5.5f, 4.3f);
	pVecResults = pVec1 + 5.3f;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << " )\n\n";


	std::cout << "__Vec3 += Vec3__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f) += (5.3f, 2.5f, 4.3f) expected answer is to override initial vector with (9.8, 10.8, 8.6)" << std::endl;
	pVec1 = Vec3(4.5f, 5.5f, 4.3f);
	pVec2 = Vec3(5.3f, 2.5f, 4.3f);
	pVec1 += pVec2;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << " )\n\n";


	std::cout << "__Vec3 += float__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f) += 5.3f expected answer is to override initial vector with (9.8, 10.8, 9.6)" << std::endl;
	pVec1 = Vec3(4.5f, 5.5f, 4.3f);
	pVec1 += 5.3f;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << " )\n\n";
	

	std::cout << std::endl << "+============== Subtraction Overloads ==================+" << std::endl;

		std::cout << "__Vec3 - Vec3__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f) - (5.3f, 2.5f, 4.3f) expected answer is (-0.8, 3.0, 0)" << std::endl;
	pVec1 = Vec3(4.5f, 5.5f, 4.3f);
	pVec2 = Vec3(5.3f, 2.5f, 4.3f);
	pVecResults = pVec1 - pVec2;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << " )\n\n";


	std::cout << "__Vec3 - float__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f) - 5.3f expected answer is (-0.8, 0.2, -1)" << std::endl;
	pVec1 = Vec3(4.5f, 5.5f, 4.3f);
	pVecResults = pVec1 - 5.3f;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << " )\n\n";


	std::cout << "__Vec3 -= Vec3__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f) -= (5.3f, 2.5f, 4.3f) expected answer is to override initial vector with (-0.8, 0.2, 0)" << std::endl;
	pVec1 = Vec3(4.5f, 5.5f, 4.3f);
	pVec2 = Vec3(5.3f, 2.5f, 4.3f);
	pVec1 -= pVec2;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << " )\n\n";


	std::cout << "__Vec3 -= float__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f) -= 5.3f expected answer is to override initial vector with (-0.8, 0.2, -1)" << std::endl;
	pVec1 = Vec3(4.5f, 5.5f, 4.3f);
	pVec1 -= 5.3f;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << " )\n\n";
	

	std::cout << std::endl << "+================ Division Overloads ================+" << std::endl;

	std::cout << "__Vec3 / Vec3__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f) / (5.3f, 2.5f, 4.3f) expected answer is (0.849, 2.2, 1)" << std::endl;
	pVec1 = Vec3(4.5f, 5.5f, 4.3f);
	pVec2 = Vec3(5.3f, 2.5f, 4.3f);
	pVecResults = pVec1 / pVec2;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << " )\n\n";


	std::cout << "__Vec3 / float__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f) / 5.3f expected answer is (0.849, 1.03, 0.81)" << std::endl;
	pVec1 = Vec3(4.5f, 5.5f, 4.3f);
	pVecResults = pVec1 / 5.3f;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << " )\n\n";


	std::cout << "__Vec3 /= Vec3__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f) /= (5.3f, 2.5f, 4.3f) expected answer is to override initial vector with (0.849, 1.03, 0.81)" << std::endl;
	pVec1 = Vec3(4.5f, 5.5f, 4.3f);
	pVec2 = Vec3(5.3f, 2.5f, 4.3f);
	pVec1 /= pVec2;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << " )\n\n";

	std::cout << "__Vec3 /= float__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f) /= 5.3f expected answer is to override initial vector with (0.849, 1.03, 0.81)" << std::endl;
	pVec1 = Vec3(4.5f, 5.5f, 4.3f);
	pVec1 /= 5.3f;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << " )\n\n";

	std::cout << std::endl << "+================ Multiplication Overloads ================+" << std::endl;

	std::cout << "__Vec3 * Vec3__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f) * (5.3f, 2.5f, 4.3f) expected answer is (23.85, 13.75, 18.49)" << std::endl;
	pVec1 = Vec3(4.5f, 5.5f, 4.3f);
	pVec2 = Vec3(5.3f, 2.5f, 4.3f);
	pVecResults = pVec1 * pVec2;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << " )\n\n";


	std::cout << "__Vec3 * float__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f) * 5.3f expected answer is (23.80, 29.15, 22.79)" << std::endl;
	pVec1 = Vec3(4.5f, 5.5f, 4.3f);
	pVecResults = pVec1 * 5.3f;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << " )\n\n";


	std::cout << "__Vec3 *= Vec3__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f) *= (5.3f, 2.5f, 4.3f) expected answer is to override initial vector with (23.80, 29.15, 22.79)" << std::endl;
	pVec1 = Vec3(4.5f, 5.5f, 4.3f);
	pVec2 = Vec3(5.3f, 2.5f, 4.3f);
	pVec1 *= pVec2;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << " )\n\n";


	std::cout << "__Vec3 *= float__" << std::endl << std::endl;
	std::cout << "\t(4.5f, 5.5f, 4.3f) *= 5.3f expected answer is to override initial vector with (23.80, 29.15, 22.79)" << std::endl;
	pVec1 = Vec3(4.5f, 5.5f, 4.3f);
	pVec1 *= 5.3f;
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << " )\n\n";

	//+=========
	//Other Functions
	std::cout << std::endl << "+=============== Get magnitude =================+" << std::endl;

	std::cout << "__GetMagnitude()__" << std::endl << std::endl;
	std::cout << "\tVec3(4.5f, 5.5f, 4.3f).GetMagnitude()) expected answer is (8.306)" << std::endl;
	pVec1 = Vec3(4.5f, 5.5f, 4.3f);
	fResults = pVec1.GetMagnitude();
	std::cout << "\tActual output is: ( " << fResults << " )\n\n";

	std::cout << std::endl << "+=============== Normalise Vector =================+" << std::endl;

	std::cout << "__NormaliseVec3()__" << std::endl << std::endl;
	std::cout << "\tVec3(4.5f, 5.5f, 4.3f).NormaliseVec3()) expected answer is (0.541, 0.662, 0.517)" << std::endl;
	pVec1 = Vec3(4.5f, 5.5f, 4.3f);
	pVecResults = pVec1.NormaliseVec3();
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << " )\n\n";

	std::cout << std::endl << "+=============== Linear Interpolation =================+" << std::endl;

	std::cout << "__LinearInterpolation( const Vec3& a_pVec1, float a_fDest )__" << std::endl << std::endl;
	std::cout << "\tVec3(4.5f, 5.5f, 4.3f).LinearInterpolation(Vec3(5.3f, 2.5f, 4.3f), 5.f) expected answer is (-20.5, -19.5, -20.7)" << std::endl;
	pVec1 = Vec3(4.5f, 5.5f, 4.3f);
	pVec2 = Vec3(5.3f, 2.5f, 4.3f);
	pVecResults = pVec1.LinearInterpolation(pVec2, 5);
	std::cout << "\tActual output is: ( " << pVecResults.m_fX << ", " << pVecResults.m_fY << ", " << pVecResults.m_fZ << " )\n\n";

	std::cout << std::endl << "+=============== Dot Product =================+" << std::endl;

	std::cout << "__DotProduct( const Vec3& a_pVec1 )__" << std::endl << std::endl;
	std::cout << "\tVec3(4.5f, 5.5f, 4.3f).DotProduct(Vec3(5.3f, 2.5f, 4.3f)) expected answer is (56.09)" << std::endl;
	pVec1 = Vec3(4.5f, 5.5f, 4.3f);
	pVec2 = Vec3(5.3f, 2.5f, 4.3f);
	fResults = pVec1.DotProduct(pVec2);
	std::cout << "\tActual output is: ( " << fResults << " )\n\n";

	std::cout << std::endl << "+=============== Get Angle =================+" << std::endl;

	std::cout << "__GetAngle( const Vec3& a_pVec1 )__" << std::endl << std::endl;
	std::cout << "\tVec3(5.f, 5.f, 4.3f).DotProduct(Vec3(0.f, 5.f, 4.3f)) expected answer is (90)" << std::endl;
	pVec1 = Vec3(5.f, 5.f, 4.3f);
	pVec2 = Vec3(5.f, -5.f, 4.3f);
	fResults = pVec1.GetAngle(pVec2);
	std::cout << "\tActual output is: ( " << fResults << " )\n\n";
}

#endif //_VECTOR3_H_