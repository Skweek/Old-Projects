
@echo off

goto :CreatePythonEnvironmentVariables
==========================================================================================
CreatePythonEnvironmentVariables
  Usage:
    This script sets up the environment variables for Python 2.6.x 

  Notes:
   setx -m the -m flag sets environment variables for all users

==========================================================================================
:CreatePythonEnvironmentVariables
setx PYTHONHOME "C:\PYTHON26"
setx PYTHONPATH "C:\PYTHON26;C:\PYTHON26\INCLUDE;C:\PYTHON26\DLLS;C:\PYTHON26\LIB;C:\PYTHON26\LIB\LIB-TK"
setx PYTHONLIBS "C:\PYTHON26\LIBS;"
pause
@echo off