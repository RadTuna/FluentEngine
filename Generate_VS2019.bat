@echo off

echo 1. Deleting intermediate folder and lib files (from the binary directory)...
del	/S /Q "Binaries\*"
del	/S /Q "Intermediate\*"
echo:

echo 2. Generating Visual Studio 2019 solution...
@ThirdParty\premake\premake5.exe --file=ThirdParty\premake\premake.lua vs2019 %cd%

pause

exit /b
