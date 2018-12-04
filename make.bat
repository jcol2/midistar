@echo off
mkdir build
cd build
cmake ..
msbuild midistar.sln
cd ..