@ECHO off
REM Change to script dir:
CD "%~dp0"

REM Check directory:
FOR %%I in (.) do SET dir=%%~nxI
IF "%dir%"=="scripts"(cd ..)
SET proj_dir="%cd%"

REM Find binary:
CALL scripts/find_binary_windows

REM If we found the binary...:
IF %errorlevel%==0 (
    REM Run executable:
    CALL "build\bin\Debug\midistar.exe" %*
    CD "%proj_dir%"
)
