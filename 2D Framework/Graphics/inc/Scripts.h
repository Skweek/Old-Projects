////////////////////////////////////////////////////////////
// File: Scripts.h
// Author: Nick Smith
// Date Created: 5th August 2013
// Brief: Script Handling
////////////////////////////////////////////////////////////
#ifndef _SCRIPTS_H_
#define _SCRIPTS_H_

#include <Python.h>
#include "Utilities.h"

void InitScripts();
void UpdateScript();
void ReloadScript();
void DeInitScripts();

//\===============================================================================
// Python functions to help things a little nicer - Courtesy of Jamie Stewart
void  ParsePyTupleError( const char* a_pFunction, int a_Line );
PyObject* ImportPythonModule( const char* a_pyModuleName );
PyObject* GetHandleToPythonFunction( PyObject* a_pModule, const char* a_pFunctionName );
PyObject* CallPythonFunction( PyObject* a_pyFunction, PyObject* a_pyFuncArguments);
//\===============================================================================

// ____Python Script Functions____ //
//PyObject* PrintString( PyObject* self, PyObject* args );


// Functions called by everything else to get information from Python
Vec2 GetScreenResolution();
bool GetFullScreen();
const char* GetWindowTitle();
void CreatePathMap( Vec2 a_pMapSize, int a_iObjectCount, Vec4* a_pObjects );
std::vector<Vec2> GetPath( Vec2 a_pStart, Vec2 a_pEnd );
Vec2 FindClosest( Vec2 a_pStart, std::vector<Vec2>a_pTargets );
Vec2 FollowObject( Vec2 a_pStart, Vec2 a_pTarget );
Vec2 FleeFromObject( Vec2 a_pStart, Vec2 a_pTarget );
Vec2 Wander( Vec2 a_pStart );

#endif // _SCRIPTS_H_
