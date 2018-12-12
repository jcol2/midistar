@echo off
REM Change to script dir:
cd "%~dp0"

REM Change to source dir if we're in the scripts folder:
FOR %%I in (.) do SET dir=%%~nxI
IF "%dir%"=="scripts" (cd ..)

SET midistar_dir=%cd%
SET ext_dir=%cd%/external
SET lib_dir=%cd%/lib
SET dll_dir=%cd%/dll
SET inc_dir=%cd%/include

echo Removing build folder...
rd /q /s build

echo Removing lib folder...
rd /q /s lib
mkdir lib

echo.
echo Resetting include folder...
rd /q /s "%inc_dir%/CLI"
rd /q /s "%inc_dir%/FluidSynth"
rd /q /s "%inc_dir%/midifile"
rd /q /s "%inc_dir%/rtmidi"
rd /q /s "%inc_dir%/SFML"
del "%inc_dir%/fluidsynth.h"

echo.
echo Setting up git submodules...
git submodule init
git submodule update

echo.
echo Preparing CLI11...
cd "%ext_dir%\CLI11" || goto :error
xcopy /E "include\CLI" "%inc_dir%\CLI\" || goto :error

echo.
echo Preparing fluidsynth...
cd "%ext_dir%/fluidsynth"
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE="C:\Program Files\vcpkg\scripts\buildsystems\vcpkg.cmake" -Denable-pkgconfig:BOOL="0" || goto :error
msbuild FluidSynth.sln || goto :error
copy "src\Debug\*.lib" "%lib_dir%\." || goto :error
copy "src\Debug\*.dll" "%lib_dir%\." || goto :error
xcopy /E "..\include\fluidsynth" "%inc_dir%\fluidsynth\" || goto :error
copy "include\fluidsynth.h" "%inc_dir%\." || goto :error
copy "include\fluidsynth\version.h" "%inc_dir%\fluidsynth\." || goto :error

echo.
echo Preparing midifile...
cd "%ext_dir%/midifile" || goto :error
mkdir build
cd build
cmake .. || goto :error
msbuild midifile.sln || goto :error
copy "Debug\*.lib" "%lib_dir%\." || goto :error
mkdir "%inc_dir%\midifile" || goto :error
copy "..\include\*.h" "%inc_dir%\midifile\." || goto :error

echo.
echo Preparing rtmidi...
cd "%ext_dir%/rtmidi"
copy "%midistar_dir%\scripts\rtmidi_makefile" Makefile || goto :error
nmake /A rtmidi.lib || goto :error
copy "*.lib" "%lib_dir%\." || goto :error
mkdir "%inc_dir%\rtmidi" || goto :error
copy "*.h" "%inc_dir%\rtmidi\." || goto :error

echo.
echo Preparing SFML...
cd "%ext_dir%/SFML" || goto :error
mkdir build
cd build
cmake .. || goto :error
msbuild SFML.sln || goto :error
copy "lib\Debug\*.lib" "%lib_dir%\." || goto :error
copy "lib\Debug\*.dll" "%lib_dir%\." || goto :error
xcopy /E "..\include\SFML" "%inc_dir%\SFML\" || goto :error

echo.
echo Finished! Refer to the README file for instructions on building midistar.
goto :end

:error
echo.
echo An error occured! Quitting...

:end
cd "%midistar_dir%"
