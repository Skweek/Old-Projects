
@echo off
xcopy "%~dp0.\include\*.h" "%~dp0..\..\Test\inc\math\" /y /d /r
xcopy "%~dp0.\libs\*.lib" "%~dp0..\..\Test\resources\libs\" /y /d /r
xcopy "%~dp0.\libs\*.dll" "%~dp0..\..\Test\resources\" /y /d /r

xcopy "%~dp0.\include\*.h" "%~dp0..\..\resources\Math Library\include\" /y /d /r
xcopy "%~dp0.\libs\*.lib" "%~dp0..\..\resources\Math Library\libs\" /y /d /r
xcopy "%~dp0.\libs\*.dll" "%~dp0..\..\resources\Math Library\libs\" /y /d /r

@echo off
