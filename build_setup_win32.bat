@ECHO off
REM Change to script dir:
CD "%~dp0"

REM Change to source dir if we're in the scripts folder:
FOR %%I in (.) do SET dir=%%~nxI
IF "%dir%"=="win32" (CD ..\..)

REM Setup variables:
SET midistar_dir=%CD%
SET ext_dir=%CD%\external
SET lib_dir=%CD%\lib
SET lib_dir_debug=%lib_dir%\debug
SET lib_dir_release=%lib_dir%\release
SET dll_dir=%CD%\dll
SET inc_dir=%CD%\include
SET win_script_dir=%CD%\scripts\win32

REM Find MSBuild:
ECHO.
ECHO Finding MSBuild...
WHERE msbuild
if %errorLevel% == 1 (
    ECHO Could not find MSBuild^! Please install Visual Studio 2017, open "Developer Command Prompt For VS 2017", and run this script there.
    GOTO :error
)

REM Find nmake:
ECHO.
ECHO Finding nmake...
WHERE nmake
if %errorLevel% == 1 (
    ECHO Could not find nmake^! Please install Visual Studio 2017, open "Developer Command Prompt For VS 2017", and run this script there.    GOTO :error
)

REM Find Git:
ECHO.
ECHO Finding git...
WHERE git
if %errorLevel% == 1 (
    ECHO Could not find git^! Please install git, add it to the system PATH variable, re-open the terminal, and try again.
    GOTO :error
)

REM Find CMake:
ECHO.
ECHO Finding cmake...
WHERE cmake
if %errorLevel% == 1 (
    ECHO Could not find cmake^! Please install cmake, add it to the system PATH variable, re-open the terminal, and try again.
    GOTO :error
)

REM Remove artifacts from previous builds:
ECHO.
ECHO Removing build folder...
RD /q /s build

ECHO.
ECHO Removing lib folder...
RD /q /s lib
MKDIR lib
MKDIR "lib\debug"
MKDIR "lib\release"

ECHO.
ECHO Resetting include folder...
RD /q /s "%inc_dir%\CLI"
RD /q /s "%inc_dir%\FluidSynth"
RD /q /s "%inc_dir%\midifile"
RD /q /s "%inc_dir%\rtmidi"
RD /q /s "%inc_dir%\SFML"
DEL "%inc_dir%\fluidsynth.h"

REM Install SoundFont:
ECHO.
ECHO Installing Fluid SoundFont...
CALL "%win_script_dir%\install_soundfont.bat" Debug

REM If we could not install the SoundFont...
IF NOT %errorlevel%==0 (
    ECHO Could not install SoundFont^!
    GOTO :error
)

REM Setup git submodules:
ECHO.
ECHO Setting up git submodules...
git submodule init
git submodule update

REM Setup pre-requisites:
ECHO.
ECHO Preparing vcpkg...
CD "%ext_dir%\vcpkg" || GOTO :error
CALL bootstrap-vcpkg.bat
IF NOT %errorlevel%==0 (
    GOTO :error
)
vcpkg install glib --triplet x64-windows || GOTO :error

ECHO.
ECHO Preparing CLI11...
CD "%ext_dir%\CLI11" || GOTO :error
git clean -fdx
XCOPY /E "include\CLI" "%inc_dir%\CLI\" || GOTO :error

ECHO.
ECHO Preparing fluidsynth...
CD "%ext_dir%\fluidsynth"
git clean -fdx
MKDIR build
CD build
cmake -A x64 .. -DCMAKE_TOOLCHAIN_FILE="%ext_dir%\vcpkg\scripts\buildsystems\vcpkg.cmake" -Denable-pkgconfig:BOOL="0" || GOTO :error
msbuild FluidSynth.sln /p:Configuration=Debug || GOTO :error
COPY "src\Debug\*.lib" "%lib_dir_debug%\." || GOTO :error
COPY "src\Debug\*.dll" "%lib_dir_debug%\." || GOTO :error
msbuild FluidSynth.sln /p:Configuration=Release || GOTO :error
COPY "src\Release\*.lib" "%lib_dir_release%\." || GOTO :error
COPY "src\Release\*.dll" "%lib_dir_release%\." || GOTO :error
XCOPY /E "..\include\fluidsynth" "%inc_dir%\fluidsynth\" || GOTO :error
COPY "include\fluidsynth.h" "%inc_dir%\." || GOTO :error
COPY "include\fluidsynth\version.h" "%inc_dir%\fluidsynth\." || GOTO :error

ECHO.
ECHO Preparing midifile...
CD "%ext_dir%\midifile" || GOTO :error
git clean -fdx
MKDIR build
CD build
cmake -A x64 .. || GOTO :error
msbuild midifile.sln /p:Configuration=Debug || GOTO :error
COPY "Debug\*.lib" "%lib_dir_debug%\." || GOTO :error
msbuild midifile.sln /p:Configuration=Release || GOTO :error
COPY "Release\*.lib" "%lib_dir_release%\." || GOTO :error
MKDIR "%inc_dir%\midifile" || GOTO :error
COPY "..\include\*.h" "%inc_dir%\midifile\." || GOTO :error

ECHO.
ECHO Preparing rtmidi...
CD "%ext_dir%\rtmidi" || GOTO :error
git clean -fdx
COPY "%win_script_dir%\rtmidi_debug_makefile" Makefile || GOTO :error
nmake /A rtmidi-d.lib || GOTO :error
COPY "*.lib" "%lib_dir_debug%\." || GOTO :error
COPY "%win_script_dir%\rtmidi_release_makefile" Makefile || GOTO :error
nmake /A rtmidi.lib || GOTO :error
COPY "*.lib" "%lib_dir_release%\." || GOTO :error
MKDIR "%inc_dir%\rtmidi" || GOTO :error
COPY "*.h" "%inc_dir%\rtmidi\." || GOTO :error

ECHO.
ECHO Preparing SFML...
CD "%ext_dir%\SFML" || GOTO :error
git clean -fdx
MKDIR build
CD build
cmake -A x64 .. || GOTO :error
msbuild SFML.sln /p:Configuration=Debug || GOTO :error
COPY "lib\Debug\*.lib" "%lib_dir_debug%\." || GOTO :error
COPY "lib\Debug\*.dll" "%lib_dir_debug%\." || GOTO :error
msbuild SFML.sln /p:Configuration=Release || GOTO :error
COPY "lib\Release\*.lib" "%lib_dir_release%\." || GOTO :error
COPY "lib\Release\*.dll" "%lib_dir_release%\." || GOTO :error
XCOPY /E "..\include\SFML" "%inc_dir%\SFML\" || GOTO :error

ECHO.
ECHO Finished setting up pre-requisites. Building midistar...
CD "%midistar_dir%"
CALL "%win_script_dir%\make.bat" Debug
if %makeerror% == 1 (
    ECHO Could not build midistar^!
    GOTO :error
)
ECHO midistar built successfully! Run using the 'run.bat' command.
ECHO Re-build in Debug mode using 'make.bat' or 'make.bat Debug'.
ECHO Re-build in Release mode using 'make.bat Release'.
ECHO Open in Visual Studio using the 'startvs.bat' command.
ECHO Refer to the README for more information.
GOTO :end

:error
ECHO.
ECHO An error occured! Quitting...

:end
CD "%midistar_dir%"
