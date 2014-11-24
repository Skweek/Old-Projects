
@echo off
xcopy "%~dp0.\inc\Framework.h" "%~dp0..\Test\inc" /y /d /r
xcopy "%~dp0.\libs\*.lib" "%~dp0..\Test\resources\libs\" /y /d /r
xcopy "%~dp0.\libs\*.dll" "%~dp0..\Test\resources\" /y /d /r

@echo off
