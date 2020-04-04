@echo off

echo 1. Deleting intermediate folder and binaries folder...
del	/S /Q "Binaries\*"
del	/S /Q "Intermediate\*"
del	/S /Q "*.sln"
echo:

echo 2. Generating Visual Studio 2019 solution...
@ThirdParty\premake\premake5.exe --file=ThirdParty\premake\premake.lua vs2019 %cd% API_GRAPHICS_D3D12

echo:
pause

exit /b
