@ECHO off
REM Change to script dir:
CD "%~dp0"

REM Change to source dir if we're in the scripts folder:
FOR %%I in (.) do SET dir=%%~nxI
IF "%dir%"=="scripts" (cd ..)

REM Call cpplint:
cpplint --root=include --recursive include\midistar\
cpplint --recursive src

