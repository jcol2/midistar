@echo off
SET midistar_dir=%cd%
SET ext_dir=%cd%/external
SET lib_dir=%cd%/lib
SET dll_dir=%cd%/dll

echo Resetting dll folder...
rd /q /s dll
mkdir dll

echo.
echo Resetting lib folder...
rd /q /s lib
mkdir lib

echo.
echo Setting up git submodules...
git submodule init
git submodule update

echo Building fluidsynth...
cd "%ext_dir%/fluidsynth"
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE="C:\Program Files\vcpkg\scripts\buildsystems\vcpkg.cmake" -Denable-pkgconfig:BOOL="0" || goto :error
msbuild FluidSynth.sln || goto :error
copy "src\Debug\*.lib" "%lib_dir%\." || goto :error
copy "src\Debug\*.dll" "%dll_dir%\." || goto :error

echo.
echo Building midifile...
cd "%ext_dir%/midifile" || goto :error
mkdir build
cd build
cmake .. || goto :error
msbuild midifile.sln || goto :error
copy "Debug\*.lib" "%lib_dir%\." || goto :error

echo.
echo Building rtmidi...
cd "%ext_dir%/rtmidi"
copy "%midistar_dir%\scripts\rtmidi_makefile" Makefile || goto :error
nmake /A rtmidi.lib || goto :error
copy "*.lib" "%lib_dir%\." || goto :error

echo.
echo Building SFML...
cd "%ext_dir%/SFML" || goto :error
mkdir build
cd build
cmake .. || goto :error
msbuild SFML.sln || goto :error
copy "lib\Debug\*.lib" "%lib_dir%\." || goto :error
copy "lib\Debug\*.dll" "%dll_dir%\." || goto :error

echo.
echo Finished! Refer to the README file for instructions on building midistar.
goto :end

:error
echo.
echo An error occured! Quitting...

:end
cd "%midistar_dir%"
