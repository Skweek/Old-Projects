
@echo off
xcopy "%~dp0.\include\*.h" "%~dp0..\..\Retro Game\Retro Game\libs\Maths\include\" /y /d /r
xcopy "%~dp0.\libs\*.lib" "%~dp0..\..\Retro Game\Retro Game\libs\Maths\lib\" /y /d /r
xcopy "%~dp0.\libs\*.dll" "%~dp0..\..\Retro Game\Retro Game\resources\" /y /d /r

@echo off
