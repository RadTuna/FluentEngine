@echo off

echo 1. Deleting intermediate folder and binaries folder...
del	/S /Q "Binaries\*"
del	/S /Q "Intermediate\*"
del	/S /Q "*.sln"
echo:

echo 2. Generating Visual Studio 2017 solution...
@ThirdParty\premake\premake5.exe --file=ThirdParty\premake\premake.lua vs2017 %cd% d3d11

echo:
pause

exit /b
