#include "Scripts.h"

// Main python module ( main.py )
PyObject* pModule;
// Function Lookup table
PyMethodDef pMethods[] = {
	//{ "Print", PrintString, METH_VARARGS, "Adds tabs and stuff to a string of text." },
	{ NULL, NULL, 0, NULL }	
};

void InitScripts()
{
	// Init Python
	Py_Initialize();
	
	// Set path to current directory
	PyObject* sysPath = PySys_GetObject((char*)"path");
	PyList_Append(sysPath, PyBytes_FromString("./scripts"));

	// Create main module
	Py_InitModule( "Game", pMethods );
	pModule = ImportPythonModule( "main" );

	PyObject* Init = GetHandleToPythonFunction( pModule, "InitialiseScript" );
	if( Init )
	{
		// Set any args here, for now none are needed
		PyObject* pReturn = CallPythonFunction( Init, nullptr );
		if( pReturn )
		{
			Py_DECREF( pReturn );
		}
		Py_XDECREF( Init );
	}

}

void ReloadScript()
{
	PyImport_ReloadModule( pModule );
}

void DeInitScripts()
{
	Py_DECREF( pModule );
	Py_Finalize();
}

void  ParsePyTupleError(const char* a_pFunction, int a_Line )
{
	std::cout << "___Error Parsing Tuple___\nFunction: " <<  a_pFunction << "\nLine#   : " << a_Line << std::endl;
	PyErr_Print();
}

PyObject* ImportPythonModule( const char* a_pyModuleName )
{
	PyObject* pObjName= PyString_FromString(a_pyModuleName);
	PyObject* pModule = PyImport_Import(pObjName);
	if (!pModule)
    {
        PyErr_Print();
        std::cout << stderr << "Failed to load \" " << a_pyModuleName << "\"" << std::endl;
    }
    Py_DECREF(pObjName);
	return pModule;
}

PyObject* GetHandleToPythonFunction( PyObject* a_pModule, const char* a_pFunctionName )
{
	 PyObject* pFunction = PyObject_GetAttrString(a_pModule, a_pFunctionName);
    /* pFunc is a new reference */
    if( !(pFunction && PyCallable_Check(pFunction)) ) 
	{
        if (PyErr_Occurred())
        {
			PyErr_Print();
		}
        std::cout << stderr << "Cannot find function \"" << a_pFunctionName << "\"" << std::endl;
    }
	return pFunction;
}

PyObject* CallPythonFunction( PyObject* a_pyFunction, PyObject* a_pyFuncArguments)
{
	PyObject* pReturnValue = PyObject_CallObject( a_pyFunction, a_pyFuncArguments );
    if (pReturnValue == nullptr)
	{
		PyErr_Print();
		fprintf(stderr,"Call failed\n");
    }
	return pReturnValue;
}

Vec2 GetScreenResolution()
{
	Vec2 resolution;
	PyObject* GetRes = GetHandleToPythonFunction( pModule, "GetResolution" );
	if( GetRes )
	{		
		PyObject* pReturn = CallPythonFunction( GetRes, nullptr );
		if( pReturn )
		{
			if ( !PyArg_ParseTuple( pReturn, "ff", &resolution[0], &resolution[1] ) ) 
			{
				ParsePyTupleError( __func__, __LINE__ );
			}

			Py_DECREF( pReturn );
		}
		Py_XDECREF( GetRes );
	}

	return resolution;
}

void CreatePathMap( Vec2 a_pMapSize, int a_iObjectCount, Vec4* a_pObjects )
{
	PyObject* MakeMap = GetHandleToPythonFunction( pModule, "CreateMap" );
	if( MakeMap )
	{
		PyObject* ObjX = PyList_New( a_iObjectCount );
		PyObject* ObjY = PyList_New( a_iObjectCount );
		PyObject* ObjW = PyList_New( a_iObjectCount );
		PyObject* ObjH = PyList_New( a_iObjectCount );

		for( int i = 0; i < a_iObjectCount; ++i )
		{
			PyObject* pX = PyInt_FromLong( (long)a_pObjects[i].m_fX );
			PyObject* pY = PyInt_FromLong( (long)a_pObjects[i].m_fY );
			PyObject* pW = PyInt_FromLong( (long)a_pObjects[i].m_fZ );
			PyObject* pH = PyInt_FromLong( (long)a_pObjects[i].m_fW );

			PyList_Insert( ObjX, i, pX );
			PyList_Insert( ObjY, i, pY );
			PyList_Insert( ObjW, i, pW );
			PyList_Insert( ObjH, i, pH );
		}

		PyObject* pArgs = PyTuple_New( 7 );
		PyTuple_SetItem( pArgs, 0, PyInt_FromLong( (long)a_pMapSize[0] ) );
		PyTuple_SetItem( pArgs, 1, PyInt_FromLong( (long)a_pMapSize[1] ) );
		PyTuple_SetItem( pArgs, 2, PyInt_FromLong( (long)a_iObjectCount ) );
		PyTuple_SetItem( pArgs, 3, ObjX );
		PyTuple_SetItem( pArgs, 4, ObjY );
		PyTuple_SetItem( pArgs, 5, ObjW );
		PyTuple_SetItem( pArgs, 6, ObjH );

		PyObject* pReturn = CallPythonFunction( MakeMap, pArgs );
		if( pReturn )
		{
			Py_DECREF( pReturn );
		}
		Py_XDECREF( MakeMap );
	}
}

std::vector<Vec2> GetPath( Vec2 a_pStart, Vec2 a_pEnd )
{
	int iPathLength;
	std::vector<Vec2> pPath;

	PyObject* FindPath = GetHandleToPythonFunction( pModule, "GetPath" );

	if( FindPath )
	{
		// Find the path
		PyObject* Start = PyList_New( 2 );
		PyObject* End = PyList_New( 2 );
		PyList_Insert( Start, 0, PyInt_FromLong( (long)a_pStart[0] ) );
		PyList_Insert( Start, 1, PyInt_FromLong( (long)a_pStart[1] ) );
		PyList_Insert( End, 0, PyInt_FromLong( (long)a_pEnd[0] ) );
		PyList_Insert( End, 1, PyInt_FromLong( (long)a_pEnd[1] ) );

		PyObject* pPathArgs = PyTuple_New( 2 );
		PyTuple_SetItem( pPathArgs, 0, Start );
		PyTuple_SetItem( pPathArgs, 1, End );

		PyObject* pReturn = CallPythonFunction( FindPath, pPathArgs );
		if( pReturn )
		{
			PyObject* pList;
			PyObject* pListItem;

			// Get path
			if ( !PyArg_ParseTuple(pReturn, "iO", &iPathLength , &pList ) ) 
			{
				ParsePyTupleError( __func__, __LINE__ );
			}
			
			for( int i = 0; i < iPathLength*2; i+=2 )
			{
				Vec2 pPathNode;
				pListItem = PyList_GetItem( pList, i ); // Get the X coord
				pPathNode.m_fX = (float)PyInt_AsLong( pListItem );
				pListItem = PyList_GetItem( pList, i+1 ); // Get the Y coord
				pPathNode.m_fY = (float)PyInt_AsLong( pListItem );
				pPath.push_back( pPathNode );
			}
			pPath.push_back( Vec2( -1, -1 ) );

			Py_DECREF( pReturn );
		}

		Py_XDECREF( FindPath );
	}
	
	return pPath;
}

Vec2 FindClosest( Vec2 a_pStart, std::vector<Vec2>a_pTargets )
{
	Vec2 pNewVelocity;

	PyObject* FindPath = GetHandleToPythonFunction( pModule, "FindClosest" );

	if( FindPath )
	{
		// Find the path
		PyObject* Start = PyList_New( 2 );
		PyObject* Count = PyInt_FromLong( (long)a_pTargets.size() );
		PyObject* Targets = PyList_New( a_pTargets.size() );

		PyList_Insert( Start, 0, PyInt_FromLong( (long)a_pStart[0] ) );
		PyList_Insert( Start, 1, PyInt_FromLong( (long)a_pStart[1] ) );

		for( int i = 0; i < (int)a_pTargets.size(); ++i )
		{			
			PyObject* TargetPos = PyTuple_New( 2 );
			PyTuple_SetItem( TargetPos, 0, PyInt_FromLong( (long)a_pTargets[i].m_fX ) );
			PyTuple_SetItem( TargetPos, 1, PyInt_FromLong( (long)a_pTargets[i].m_fY ) );
			PyList_Insert( Targets, i, TargetPos );
		}

		PyObject* pPathArgs = PyTuple_New( 3 );
		PyTuple_SetItem( pPathArgs, 0, Start );
		PyTuple_SetItem( pPathArgs, 1, Count );
		PyTuple_SetItem( pPathArgs, 2, Targets );

		PyObject* pReturn = CallPythonFunction( FindPath, pPathArgs );
		if( pReturn )
		{
			float xVal, yVal;

			// Get path
			if ( !PyArg_ParseTuple(pReturn, "ff", &xVal, &yVal ) ) 
			{
				ParsePyTupleError( __func__, __LINE__ );
			}
			pNewVelocity.m_fX = (float)xVal;
			pNewVelocity.m_fY = (float)yVal;

			Py_DECREF( pReturn );
		}

		Py_XDECREF( FindPath );
	}
	
	return pNewVelocity;
}

Vec2 FleeFromObject( Vec2 a_pStart, Vec2 a_pTarget )
{
	Vec2 pNewVelocity;

	PyObject* Follow = GetHandleToPythonFunction( pModule, "Flee" );

	if( Follow )
	{
		// Find the path
		PyObject* Start = PyList_New( 2 );
		PyObject* End = PyList_New( 2 );
		PyList_Insert( Start, 0, PyInt_FromLong( (long)a_pStart[0] ) );
		PyList_Insert( Start, 1, PyInt_FromLong( (long)a_pStart[1] ) );
		PyList_Insert( End, 0, PyInt_FromLong( (long)a_pTarget[0] ) );
		PyList_Insert( End, 1, PyInt_FromLong( (long)a_pTarget[1] ) );

		PyObject* pPathArgs = PyTuple_New( 2 );
		PyTuple_SetItem( pPathArgs, 0, Start );
		PyTuple_SetItem( pPathArgs, 1, End );

		PyObject* pReturn = CallPythonFunction( Follow, pPathArgs );
		if( pReturn )
		{
			float xVal, yVal;

			// Get path
			if ( !PyArg_ParseTuple(pReturn, "ff", &xVal, &yVal ) ) 
			{
				ParsePyTupleError( __func__, __LINE__ );
			}
			pNewVelocity.m_fX = (float)xVal;
			pNewVelocity.m_fY = (float)yVal;
			Py_DECREF( pReturn );
		}

		Py_XDECREF( Follow );
	}
	
	return pNewVelocity;
}

Vec2 Wander( Vec2 a_pStart )
{
	Vec2 pNewVelocity;

	PyObject* Follow = GetHandleToPythonFunction( pModule, "Wander" );

	if( Follow )
	{
		// Find the path
		PyObject* Start = PyList_New( 2 );
		PyList_Insert( Start, 0, PyInt_FromLong( (long)a_pStart[0] ) );
		PyList_Insert( Start, 1, PyInt_FromLong( (long)a_pStart[1] ) );

		PyObject* pPathArgs = PyTuple_New( 1 );
		PyTuple_SetItem( pPathArgs, 0, Start );

		PyObject* pReturn = CallPythonFunction( Follow, pPathArgs );
		if( pReturn )
		{
			float xVal, yVal;

			// Get path
			if ( !PyArg_ParseTuple(pReturn, "ff", &xVal, &yVal ) ) 
			{
				ParsePyTupleError( __func__, __LINE__ );
			}
			pNewVelocity.m_fX = (float)xVal;
			pNewVelocity.m_fY = (float)yVal;
			Py_DECREF( pReturn );
		}

		Py_XDECREF( Follow );
	}
	
	return pNewVelocity;
}

Vec2 FollowObject( Vec2 a_pStart, Vec2 a_pTarget )
{
	Vec2 pNewVelocity;

	PyObject* Follow = GetHandleToPythonFunction( pModule, "Follow" );

	if( Follow )
	{
		// Find the path
		PyObject* Start = PyList_New( 2 );
		PyObject* End = PyList_New( 2 );
		PyList_Insert( Start, 0, PyInt_FromLong( (long)a_pStart[0] ) );
		PyList_Insert( Start, 1, PyInt_FromLong( (long)a_pStart[1] ) );
		PyList_Insert( End, 0, PyInt_FromLong( (long)a_pTarget[0] ) );
		PyList_Insert( End, 1, PyInt_FromLong( (long)a_pTarget[1] ) );

		PyObject* pPathArgs = PyTuple_New( 2 );
		PyTuple_SetItem( pPathArgs, 0, Start );
		PyTuple_SetItem( pPathArgs, 1, End );

		PyObject* pReturn = CallPythonFunction( Follow, pPathArgs );
		if( pReturn )
		{
			float xVal, yVal;

			// Get path
			if ( !PyArg_ParseTuple(pReturn, "ff", &xVal, &yVal ) ) 
			{
				ParsePyTupleError( __func__, __LINE__ );
			}
			pNewVelocity.m_fX = (float)xVal;
			pNewVelocity.m_fY = (float)yVal;
			Py_DECREF( pReturn );
		}

		Py_XDECREF( Follow );
	}
	
	return pNewVelocity;
}
