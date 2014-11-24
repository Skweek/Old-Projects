//////////////////////////////////////////////////////////////////////////
#include "AIE.h"
#include <string>
#include <cmath>
#include <time.h>
#include <assert.h>
#include <crtdbg.h>
#include <iostream>

// Math library files
#include "Conversions.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Maths.h"

//+==================================
// Header files containing
// test functions
	
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include "TankTest.h"

bool running;
//
//+==================================

int main( int argc, char* argv[] )
{	
	running = true;
	system("color 4B");
	 while ( running )
	 {
		std::cout << "\n\nUnit testing..." << std::endl;
		std::cout << " 1 for visual test of matrices. \n 2 for vector 2 tests \n 3 for vector 3 tests \n 4 for vector 4 tests." << std::endl;

		int iInput;
		std::cin >> iInput;
		switch ( iInput )
		{
		case 1: // visual tank example
			TankTest();
			break;

		case 2: // vector 2
			Vector2();
			break;

		case 3: // vector 3
			Vector3();
			break;

		case 4:
			Vector4();
			break;

		default:
			running = false;
			break;
		}
	 }
	
	return 0;
}